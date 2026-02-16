# Narrative AI Tools – Unreal Engine Demo

This project demonstrates a **production-minded, AI-assisted narrative tooling system** built in Unreal Engine.

The focus is **not** on AI sophistication or autonomous storytelling, but on **system design**, **editor tooling**, and **author-controlled workflows** that integrate AI safely into real game development pipelines.

>>  Tested on Unreal Engine 5.7.
---

## Overview

The system provides:

- Structured narrative context modeling
- Explicit dialogue constraints
- AI-assisted dialogue generation
- Custom Unreal Editor tooling for writers and designers
- Debuggable, inspectable, and deterministic behavior

AI is treated as an **assistive component**, never as an autonomous decision-maker.

---

## Key Goals

- Support narrative iteration without removing authorial control
- Make AI-assisted dialogue **transparent and debuggable**
- Provide real editor tooling usable by non-programmers
- Demonstrate safe async AI integration in Unreal Engine
- Showcase production-quality C++ architecture

---

## Core Concepts

### Explicit Narrative Context

All narrative-relevant data is represented using **structured data**, never raw prompt text:

- NPC narrative mood
- Allowed and forbidden dialogue topics
- Player, NPC, and world state tags
- Explicit dialogue intent

This allows validation, inspection, and deterministic fallback behavior.

---

### Controlled AI Agency

AI is only allowed to operate **within explicit boundaries**:

- Context is authored, not inferred
- Topics can be allowed or forbidden
- Responses can be validated or rejected
- Final state changes are applied explicitly

The system intentionally avoids:
- Autonomous narrative branching
- Implicit story decisions
- Hidden state mutation

---

## Editor Tooling (Highlight)

The project includes custom Unreal Editor tooling designed to support narrative iteration.

### Features

- **Editor Utility Widget** for narrative authoring
- Multi-NPC selection directly from the level
- Per-NPC narrative configuration:
    - Mood
    - Allowed topics
    - Forbidden topics
- Live synchronization between editor UI and NPC components
- Explicit “Apply” workflow to prevent accidental state changes

### Tooling Stack

- C++ Editor module
- Editor Utility Widgets
- DetailsView integration
- Gameplay Tags
- Structured editor-only data objects

This tooling is designed to be:
- Inspectable
- Safe
- Demonstrable
- Friendly to writers and designers

---

## Dialogue Flow

1. Player initiates interaction with an NPC
2. Narrative context snapshot is built
3. A dialogue request is constructed
4. The request is sent to an AI Response Provider
5. The response is validated and logged
6. A final dialogue line is emitted
7. Narrative updates are applied explicitly

If validation fails, the system falls back to deterministic authored behavior.

---

## AI Response Providers

Dialogue generation is abstracted behind a provider interface.

### Current Provider

- Local LLM integration using **LM Studio**
- OpenAI-compatible HTTP API
- Asynchronous execution
- Safe return to Game Thread before emitting results

### Provider Architecture Enables

- Mock providers for testing
- Offline or deterministic providers
- Future cloud or hybrid integrations
- Easy replacement without touching gameplay code

---

## Debugging & Diagnostics

A core design goal is **debbugability**.

The system exposes:

- Narrative context snapshots
- Generated prompts
- Raw AI responses
- Validation results
- Final dialogue output
- Interaction history

This allows designers and engineers to understand **why** a specific line was produced.

---

## Technical Highlights

- Unreal Engine C++ (Runtime + Editor modules)
- Gameplay Tags for narrative constraints
- Editor Utility Widgets
- Asynchronous HTTP integration
- Thread-safe AI callbacks
- Clear separation between runtime and editor-only logic

---

## Scope & Non-Goals

### In Scope

- Narrative context modeling
- Dialogue interaction flow
- Editor tooling
- AI-assisted iteration workflows
- Unreal Engine integration

### Out of Scope

- Training or fine-tuning language models
- High-fidelity AI dialogue quality
- Fully autonomous narrative systems
- Large-scale content production

---

## Why This Project?

This project explores how AI-assisted narrative systems can be designed **responsibly** and **practically** for real production environments.

The goal is to demonstrate how AI can **empower creators**, not replace them — through tooling, structure, and explicit control.

---

>> Note: Local LLM behavior may vary depending on model alignment.
The system is designed to enforce constraints, but smaller instruct models may occasionally violate formatting rules.

## Author

**Wanderson Lopes**  
Systems / Gameplay Engineer  
Unreal Engine • C++ • Tools • AI-assisted workflows

