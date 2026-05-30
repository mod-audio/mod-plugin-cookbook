# CLAUDE.md — shared context for the cookbook

Read this first at the start of every session before touching files.
Update it when decisions change. Public file — yes, even though it
mostly documents working notes — because transparency about how the
project evolves is in keeping with the cookbook's open spirit.

## What this is

`mod-plugin-cookbook` is a public collection of AI prompts and worked
recipes that lets non-developers turn a sound-design idea into a
working plugin for MOD devices. The flow:

1. User sends an AI of their choice a link to this repo (or pastes
   the prompt content directly).
2. AI reads `prompts/plugin-from-idea.md`, asks the user a few
   structured questions, produces a single self-contained Buildroot
   `.mk` file.
3. User uploads the `.mk` at
   [https://builder.mod.audio/buildroot](https://builder.mod.audio/buildroot)
   with a MOD unit connected over USB. Plugin builds, installs, runs.

The cookbook is the lighter-weight cousin of `mod-plugin-studio` (a
separate private project): the studio is the upcoming successor to
`mod-cloud-builder`; the cookbook works against the existing service
and exists to validate "AI helps non-devs make plugins" as a real
funnel into MOD's ecosystem.

## License

MIT throughout. We accept MIT-compatible contributions only. Be
deliberate about adding any dependency or referenced library that
isn't permissively licensed.

## Strategic context

Gianfranco Ceccolini (founder, MOD Audio) frames the broader plugin
growth funnel in four phases:

1. Devs build plugins locally.
2. Devs share builds via persistent links.
3. Submit to MOD store Beta category.
4. Promote to Main.

The cookbook lives at the *entry* of that funnel — even before phase 1
for many users. A non-dev with an idea uses the cookbook to produce a
plugin, then upgrades into the existing funnel from there.

## Repo layout

```
README.md                Dual-audience entry point (humans + AIs).
LICENSE                  MIT.
CONTRIBUTING.md          How community members add recipes.
CLAUDE.md                This file. Session continuity.
prompts/
    plugin-from-idea.md  The AI prompt for "idea -> .mk file".
examples/
    gain.mk              Canonical worked example, validated on real
                         hardware.
```

## Decisions locked in

- **One canonical entry point** — the repo root README. Both humans
  and AIs land there; the README directs each appropriately.
- **AI-agnostic prompts** — the prompt works with any AI that can
  fetch URLs and produce text (Claude, ChatGPT, Gemini, others). No
  tool-use requirements.
- **Embedded source pattern** — every recipe embeds its DSP code
  and LV2 metadata inline in the `.mk` file via `define ... endef`
  make variables exported into the shell environment. No external
  git repos other than DPF.
- **DPF as the framework** — every plugin in the cookbook is
  DPF-based. Already on the build container, already used by all
  existing MOD skeletons, abstracts most LV2 complexity into one
  `Plugin` subclass.
- **Hand-written LV2 TTL files** — DPF's `lv2_ttl_generator` cannot
  run cross-compiled to ARM in the MOD builder image. So recipes
  hand-write `manifest.ttl` and `<bundle>.ttl` rather than relying
  on DPF's generator.
- **`urn:mod-cookbook:<bundle>` LV2 URI convention** — for plugins
  produced via the cookbook prompt. Users with their own brand can
  use their own URI scheme.
- **`MOD Cookbook` as default brand** — but the prompt *explicitly*
  offers the user the option to use their own name or alias if
  they're publishing under their own brand. This matters for
  community ownership.

## Current state (last updated 2026-05-30)

**Validated end-to-end on real hardware, across two AI providers and
multiple plugin shapes**

- `examples/gain.mk` — 1-in / 1-out gain. Hand-written reference,
  built and installed on Dwarf.
- Tube Screamer overdrive — Claude Chat, one-line prompt. Built and
  installed on Dwarf. Required ~+20 dB pre-gain to saturate (see open
  gap 1 below).
- `examples/ce2-chorus.mk` — Claude Chat, one-line prompt, contributed
  by Gianfranco. Demonstrates time-based DSP (delay line, LFO,
  fractional interpolation). Built and installed on Dwarf.
- Centre Filter — ChatGPT, single-knob bidirectional filter (LP left
  of centre, HP right). Built and installed; first cross-AI validation.
  Notable DSP: logarithmic frequency mapping, coefficient smoothing,
  state continuity across mode switches.

The fetch-by-URL workflow is working: user sends just the repo root
URL, the AI follows the README's "For AIs" section, fetches the prompt
and (typically) the example, produces a compliant recipe. ChatGPT
initially planned to generate a regular LV2 source tree but corrected
itself after reading the cookbook — meaningful confirmation that the
docs are doing real work.

**Open gaps tracked here, in rough priority order**

1. **MOD device signal-level guidance.** Still the biggest known gap.
   The prompt has no information about what dBFS represents in practice
   at a MOD unit's input. Saturation, distortion, dynamics, level-meter,
   compressor, and anything where absolute signal level matters all
   need this. Gain pedals don't care. Asked Gianfranco for the actual
   numbers (nominal instrument level, line-vs-instrument distinction,
   headroom convention for output, whether it differs across Dwarf /
   Duo / DuoX / Anagram); he doesn't have them at hand yet. Add to
   the prompt as a "DSP design notes for MOD devices" section once
   we have the numbers.

2. **More example shapes still valuable.** Two examples (gain,
   ce2-chorus) cover callback-only and delay-based. Future additions
   that would teach the AI new patterns: a one-pole filter (covers
   filter coefficient math), a stereo plugin (covers multi-channel
   processing), an envelope follower / dynamics plugin (covers
   per-sample envelope tracking and gain reduction). The centre-filter
   from ChatGPT could be polished into an example if Gianfranco wants
   to attribute it to himself or get permission from the AI's output
   considered uncontroversial enough to include as cookbook material.

3. **Propose-vs-proceed UX.** Tested twice now — Claude Chat's
   tube-screamer and chorus both proceeded directly without ceremonial
   confirmation. ChatGPT did the same. The prompt has been loosened
   to explicitly endorse this for already-specific requests, reserving
   propose-and-wait for genuinely open ones.

## Working rhythm

- Every session starts by reading this file.
- Public repo, so don't put anything internal/confidential here.
  Strategic context that's already public (MOD's funnel framing, the
  cookbook's reason for existing) is fine; specific pricing, partner
  names, unannounced plans are not.
- Each new recipe or prompt is a small, reviewable slice. Don't
  bundle multiple features into one PR.
- The "Current state" section above is overwritten, not appended to,
  so this file doesn't drift into a chat log.
- When a "Open gap" gets resolved, move it out of the list and into
  the historical record, or just delete it if it's no longer
  relevant. The list should always reflect what's actually open.
