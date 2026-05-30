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

**Validated end-to-end on real hardware**
- `examples/gain.mk` — 1-in / 1-out gain plugin. Built, installed,
  works on Dwarf.
- A tube screamer overdrive produced by Claude Chat from a one-line
  prompt request. Built, installed, behaves on Dwarf — though it
  needs ~+20 dB of pre-gain to actually saturate, because the AI
  didn't know what nominal signal level a MOD unit presents at its
  input. This identified the largest known gap (see below).

**Open gaps tracked here, in rough priority order**

1. **MOD device signal-level guidance.** The prompt has no information
   about what dBFS represents in practice at a MOD unit's input.
   Saturation, distortion, dynamics, level-meter, compressor, and
   anything where absolute signal level matters all need this. Gain
   pedals don't care. Asked Gianfranco for the actual numbers
   (nominal instrument level, line-vs-instrument distinction,
   headroom convention for output, whether it differs across Dwarf /
   Duo / DuoX / Anagram); he doesn't have them at hand yet. Add to
   the prompt as a "DSP design notes for MOD devices" section once
   we have the numbers.

2. **`$(TARGETS)` escape bug — fixed.** Originally our gain.mk had
   `all: $(TARGETS)` inside the DPF Makefile define block, which
   expanded to empty at export time. Claude Chat's tube-screamer
   correctly used `$$(TARGETS)`. Both the standalone gain.mk and the
   inlined version in the prompt have been corrected.

3. **Interaction pattern strengthened.** Originally the prompt told
   the AI to "ask any clarifying questions you genuinely need" —
   vague enough that the AI judged everything was clear and defaulted
   to brand=MOD Cookbook, knob ranges of its own choice, etc. Now the
   prompt instructs a structured "propose, then confirm" pass before
   generation: AI surfaces plugin name, brand (offering the user's
   own as an option), LV2 category, channel count, and knob ranges
   in one short message; user adjusts; AI generates.

4. **More recipes.** One canonical example (gain) is enough to
   demonstrate the pattern but not to teach the AI variation. Adding
   2–3 more shapes — a delay (with a circular buffer), a tremolo
   (with an LFO and time-dependent state), maybe a one-pole filter
   — would give the AI more to interpolate from when handling
   creative requests.

5. **Test the new interaction pattern.** Now that the prompt asks the
   AI to propose-then-confirm, we should test with a fresh
   conversation to verify the AI actually does that pass and the UX
   feels right.

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
