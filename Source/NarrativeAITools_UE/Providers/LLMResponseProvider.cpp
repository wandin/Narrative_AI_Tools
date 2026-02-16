// Narrative AI Tools – Wanderson Lopes (2025)

#include "LLMResponseProvider.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Prompt/DialoguePromptBuilder.h"
#include "Prompt/DialoguePromptTypes.h"

static const FString LLM_URL = TEXT("http://127.0.0.1:1234/api/v1/chat");

static const FString LLM_MODEL = TEXT("phi-3-mini-4k-instruct");


FDialogueResponse ULLMResponseProvider::GenerateResponse_Implementation(const FDialogueRequest& Request)
{
	FDialogueResponse Response;

	const FDialoguePrompt Prompt = FDialoguePromptBuilder::BuildPrompt(Request);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest =	FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(LLM_URL);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json"));
	HttpRequest->SetHeader(TEXT("User-Agent"), TEXT("UnrealEngine"));

	HttpRequest->SetContentAsString(BuildRequestBody(Prompt.System, Prompt.User));

	HttpRequest->OnProcessRequestComplete().BindLambda(
	[WeakThis = TWeakObjectPtr<ULLMResponseProvider>(this)]
	(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess)
	{
		FDialogueResponse LocalResponse;

		if (!bSuccess || !Resp.IsValid())
		{
			LocalResponse.bIsValid = false;
			LocalResponse.ValidationMessage = TEXT("LLM request failed");
		}
		else
		{
			const FString Json = Resp->GetContentAsString();
			const FString Text = WeakThis.IsValid() ? WeakThis->ExtractAssistantText(Json) : TEXT("");

			LocalResponse.bIsValid = !Text.IsEmpty();
			LocalResponse.DialogueText = FText::FromString(Text);
		}

		AsyncTask(ENamedThreads::GameThread, [WeakThis, LocalResponse]()
		{
			// PIE closed / engine closed / provider destroyed
			if (!WeakThis.IsValid() || IsEngineExitRequested())
			{
				return;
			}

			WeakThis->OnResponseReady.Broadcast(LocalResponse);
		});
	}
);

	HttpRequest->SetTimeout(30.0f);

	HttpRequest->ProcessRequest();

	Response.bIsValid = false;
	Response.ValidationMessage = TEXT("Waiting for AI response...");

	return Response;
}

FString ULLMResponseProvider::BuildRequestBody(const FString& SystemPrompt,	const FString& UserPrompt) const
{
	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();

	const FString FullPrompt = SystemPrompt + TEXT("\n\n") + UserPrompt;
	
	Root->SetStringField(TEXT("model"), LLM_MODEL);
	Root->SetNumberField(TEXT("temperature"), 0.4);
	Root->SetStringField(TEXT("input"), FullPrompt);

	FString Output;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Output);

	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
	return Output;
}

FString ULLMResponseProvider::ExtractAssistantText(const FString& JsonResponse) const
{
	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonResponse);

	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		return TEXT("");
	}

	const TArray<TSharedPtr<FJsonValue>>* OutputArray;
	if (!Root->TryGetArrayField(TEXT("output"), OutputArray))
	{
		return TEXT("");
	}

	if (OutputArray->Num() == 0)
	{
		return TEXT("");
	}

	const TSharedPtr<FJsonObject> MessageObj =
		(*OutputArray)[0]->AsObject();

	if (!MessageObj.IsValid())
	{
		return TEXT("");
	}

	FString Content;
	if (!MessageObj->TryGetStringField(TEXT("content"), Content))
	{
		return TEXT("");
	}
	
	return Content.TrimStartAndEnd();
}