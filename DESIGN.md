# AI-Assisted Narrative Tooling Demo

## 1. Goal

This project explores how AI-assisted systems can support narrative design in video games without removing authorial control.

Rather than fully automating dialogue or quest logic, the goal is to design tooling that:
- Assists writers and designers during iteration
- Preserves explicit narrative constraints
- Remains transparent, debuggable, and predictable
- Integrates cleanly into a real Unreal Engine production workflow

The focus of this demo is not AI sophistication, but system and tooling design.

---

## 2. Problem Statement

Narrative designers want reactive characters and dialogue systems that respond to player state, world context, and narrative progression.

However, fully autonomous AI systems introduce several risks:
- Loss of authorial intent
- Non-deterministic or invalid output
- Poor debuggability
- Difficult iteration and validation

This project investigates a middle ground:
AI as an assistive system operating within clearly defined boundaries.

---

## 3. Editor Tooling

To support narrative iteration, the system includes custom Unreal Editor tooling designed for real production workflows.

Key features:
- Multi-NPC selection via Editor Utility Widget
- Per-NPC narrative configuration (mood, allowed topics, forbidden topics)
- Clear separation between runtime state and editor-authored data
- Explicit "apply" workflow to avoid accidental state mutation
- Live synchronization between editor UI and in-world NPCs

All tooling is implemented using:
- C++ Editor modules
- Editor Utility Widgets
- Gameplay Tags and structured data

The editor tooling is designed to be demonstrable, inspectable,
and usable by non-programmers.

---

## 4. Design Philosophy

### Human-in-the-loop
All AI-assisted behavior is guided by explicit author-defined context and constraints.
The system never makes irreversible narrative decisions on its own.

### Explicit context
All narrative-relevant information is represented as structured data rather than free text.
This enables validation, debugging, and deterministic fallback behavior.

### Controlled AI agency
The system intentionally limits where AI has freedom and where it does not.
Different degrees of AI autonomy are treated as a design decision, not a default.

### Production-minded systems
All systems are designed to be:
- Inspectable
- Loggable
- Replayable
- Safe in asynchronous execution
- Usable by non-programmers through tooling

---

## 5. High-Level Architecture

The system is composed of four main layers:
1. Narrative Context
2. Dialogue & Interaction
3. AI Response Providers
4. Debug & Diagnostics Tooling

Each layer is intentionally decoupled to allow iteration and replacement.

---

## 6. Narrative Context

Narrative context represents the current state of the story and the player's relationship to the world.

Examples of context data:
- Player reputation
- NPC emotional state
- Active quests
- World flags
- Allowed and forbidden dialogue topics

All context is represented using structured data
(enums, gameplay tags, and structs), never raw prompt strings.

---

## 7. Dialogue & Interaction Flow

1. The player initiates an interaction with an NPC
2. A dialogue request is constructed from the current narrative context
3. The request is passed to an AI Response Provider
4. The response is validated against narrative constraints
5. A final dialogue line is selected or rejected
6. Narrative state updates are applied explicitly

If validation fails, the system falls back to deterministic authored content.

---

## 8. AI Response Providers

AI response generation is abstracted behind a provider interface.

Current implementations include:
- A local LLM provider using LM Studio (OpenAI-compatible API)

Providers are asynchronous and explicitly return to the Game Thread
before emitting results, ensuring engine safety and editor stability.

---

## 9. Debugging & Diagnostics

A core goal of the system is debuggability.

The tooling exposes:
- Current narrative context
- Dialogue prompts sent to the provider
- Raw provider responses
- Validation results
- Final-selected dialogue
- Historical interaction logs

This allows writers and designers to understand *why*
a specific line was chosen.

---

## 10. Scope and Non-Goals

### In Scope
- Narrative context modeling
- Dialogue flow and interaction
- Editor tooling and debugging workflows
- Unreal Engine integration

### Out of Scope
- Training or fine-tuning language models
- High-fidelity AI dialogue generation
- Large-scale narrative content

---

## 11. Why This Project?

This demo explores how AI-assisted narrative systems can be designed responsibly and practically for real production environments.

The goal is to build systems that empower creators rather than replace them.
