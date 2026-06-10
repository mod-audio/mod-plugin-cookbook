# CLAUDE.md — shared context for the cookbook

Read this first at the start of every session before touching files.
Update it when decisions change. Public file — yes, even though it
mostly documents working notes — because transparency about how the
project evolves is in keeping with the cookbook's open spirit.

## What this is

`mod-plugin-cookbook` is a public collection of AI prompts and worked
recipes that lets non-developers turn a sound-design idea into a
working plugin for devices in the MOD ecosystem. The flow:

1. User sends an AI of their choice a link to this repo (or pastes
   the prompt content directly).
2. AI reads `prompts/plugin-from-idea.md`, asks the user a few
   structured questions, produces a single self-contained Buildroot
   `.mk` file.
3. User uploads the `.mk` at
   [https://builder.mod.audio/buildroot](https://builder.mod.audio/buildroot)
   with a unit connected over USB. Plugin builds, installs, runs.

The cookbook is intentionally narrow: one prompt, one deliverable
shape, one excellent path. Both serve MOD's broader strategic role —
see "Strategic context for the project" below.

## Strategic context for the project

Future sessions read this before making product decisions. Captured
here so the cookbook's positioning stays consistent.

**MOD's role in the ecosystem.** MOD's commercial business is selling
two services to embedded-Linux audio device manufacturers: the
Marketplace cloud infrastructure (for distributing plugins to users)
and the Licensing API (a libmodla-based DRM system with trial/full
modes that lets developers freely distribute plugins, with licenses
generated server-side and tied to specific device hardware IDs). MBS
— the Buildroot-based build kitchen — was sold to Darkglass during
the Anagram deal; MOD cannot use it for new devices but Darkglass
can. MOD's strategic moat is now the marketplace + licensing combo,
which any embedded-Linux audio platform can buy as a service.

**Cookbook's strategic role.** Open-source ecosystem investment, not
a direct revenue product. More plugins → richer marketplace →
stronger pitch when selling marketplace+licensing services to device
manufacturers. The cookbook lowers the barrier to creating ecosystem-
compatible plugins, which feeds the long-term moat. It also signals
"MOD has a healthy, accessible developer story" to potential
customers evaluating MOD as a platform partner.

**Ecosystem framing, not MOD-device framing.** Plugins built via the
cookbook target the shared LV2/DPF/mod-host foundation. They run on
MOD's own devices (Dwarf/Duo/DuoX), on Darkglass Anagram, and on any
future device built on the same Linux/JACK/mod-host stack (e.g. the
Darkglass-Blackstar device under discussion). Cookbook language and
positioning should reflect this — "MOD ecosystem," not "MOD device
only." Plugins are portable across the ecosystem; that portability
is part of what makes MOD's marketplace-as-a-service pitch
compelling.

**Relationship with Darkglass.** Darkglass is simultaneously: a
current customer (uses MBS, may become a marketplace customer), a
downstream platform (Anagram built on MOD's open-source stack), and
the employer of falkTX (long-time MOD maintainer of mod-host, DPF,
mod-plugin-builder). Their [Plugin-Dev-Setup repo](https://github.com/Darkglass-Electronics/Plugin-Dev-Setup)
documents Anagram-specific developer concerns. Cross-linking is
appropriate and mutual: their docs cover Anagram polish, the cookbook
covers ecosystem creation. Neither subordinates the other.

**MOD's distinct product surface inside the shared foundation.**
modgui (the web-based pedal-face UI) is MOD's specifically — Anagram
uses LVGL on its own screen. Investing in cookbook modgui templates
is investing in MOD's product differentiation within the shared
ecosystem. This is the planned next major piece of cookbook work
(see open gaps).

## Strategic context — plugin funnel

Gianfranco Ceccolini (founder, MOD Audio) frames the plugin growth
funnel in four phases:

1. Devs build plugins locally.
2. Devs share builds via persistent links.
3. Submit to MOD store Beta category.
4. Promote to Main.

The cookbook lives at the *entry* of that funnel — even before phase 1
for many users. A non-dev with an idea uses the cookbook to produce a
plugin, then upgrades into the existing funnel from there.

The funnel feeds MOD's marketplace + licensing services (see
"Strategic context for the project" above) — more plugins flowing
through the funnel means more catalogue value when pitching marketplace
services to device-manufacturer customers.

## License

MIT throughout. We accept MIT-compatible contributions only. Be
deliberate about adding any dependency or referenced library that
isn't permissively licensed.

## Repo layout

```
README.md                Dual-audience entry point (humans + AIs).
LICENSE                  MIT.
CONTRIBUTING.md          How community members add recipes.
CLAUDE.md                This file. Session continuity.
prompts/
    plugin-from-idea.md  The AI prompt for "idea -> .mk file".
examples/
    gain.mk              Canonical worked example, validated on
                         real hardware.
    ce2-chorus.mk        Contributed example by Gianfranco;
                         demonstrates time-based DSP.
```

## Decisions locked in

- **One canonical entry point** — the repo root README. Both humans
  and AIs land there; the README directs each appropriately.
- **One canonical workflow.** A single prompt, one deliverable
  shape, deliberately narrow scope. Earlier work added a project-
  mode workflow alongside the prototype one; it confused the AIs by
  giving them a choice the user hadn't asked for, and was rolled
  back. See "Path-2 rollback" below.
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
  run cross-compiled to ARM in the MOD builder image. Recipes
  hand-write `manifest.ttl` and `<bundle>.ttl` rather than relying
  on DPF's generator.
- **`urn:mod-cookbook:<bundle>` LV2 URI convention** — for plugins
  produced via the cookbook prompt. Users with their own brand can
  use their own URI scheme.
- **`MOD Cookbook` as default brand** — but the prompt *explicitly*
  offers the user the option to use their own name or alias if
  they're publishing under their own brand. This matters for
  community ownership.

## Path-2 rollback (recorded for continuity)

A "project mode" workflow was added in a previous iteration — a
second prompt (`plugin-as-project.md`) and a directory-tree example
(`projects/gain/`) that produced a small repo the user would host on
git rather than a single embedded `.mk`. The intent was to support
iteration, multi-file DSP, external dependencies, and eventually a
modgui pedal face — all of which the single-file path can't do
well.

After posting the path-1 cookbook to forum.mod.audio and seeing real
community use, Gianfranco observed that adding path 2 made the
cookbook *worse overall*:

- AIs reading the README saw two options and had to choose.
- They sometimes routed users into the project workflow (asking
  about GitHub, repo URLs, file trees) when the user just wanted a
  quick `.mk` from a description.
- The "ask first which path" friction reduced the lean,
  send-link-get-result UX that had been working well.

We rolled back to path-1-only as the public surface. Files were
deleted; git history preserves the work. Rationale, in case we
revisit: the cookbook's strength is being a single-purpose tool. If
project-mode work matters in the future, it probably belongs in a
separate repo or in `mod-plugin-studio` rather than expanding the
cookbook's scope.

Specifically don't do without strong new evidence:
- Add a second prompt that an AI might choose between.
- Branch the README into multiple paths.
- Introduce decisions the user didn't ask the AI to make.

A related cleanup was made immediately after the rollback: the README's
"Related projects in the ecosystem" section pointing at the Darkglass
Plugin-Dev-Setup repo was also removed, along with the explicit
Darkglass-Anagram mention in the opening paragraph. The reasoning:
the cookbook's audience is non-coders with sound-design ideas; pointing
them at a porting-and-build-environment doc is irrelevant or
confusing. The ecosystem story can live in MOD's broader docs and
sales material; the cookbook should serve cookbook users. The
Darkglass relationship and strategic positioning still belong in this
file's "Strategic context" section above (internal session continuity
needs them), but they don't belong in the public README.

Specifically also don't do without strong new evidence:
- Re-add cross-links to partner platforms in the public README.
- Reframe the cookbook around an "ecosystem" pitch rather than the
  direct "describe an idea, get a plugin" pitch.

## Current state (last updated 2026-06-10)

**Path 1 validated, shipped to the community, working well.**

- Cookbook is live and announced on forum.mod.audio. Reception was
  positive; non-coders particularly enjoy the "pull a plugin out of
  thin air" experience.
- Validated end-to-end with four plugins built and installed on a
  Dwarf, across Claude and ChatGPT: gain (`examples/gain.mk`), tube
  screamer (Claude Chat, one-line prompt), CE-2 chorus
  (`examples/ce2-chorus.mk`, contributed by Gianfranco), and a
  one-knob bidirectional filter (ChatGPT).
- Strategic framing is in place: README and CLAUDE.md describe the
  cookbook as ecosystem-positioned, cross-linked to Darkglass's
  Plugin-Dev-Setup as the right home for Anagram-specific developer
  work.

**Open gaps tracked here, in rough priority order**

1. **MOD device signal-level guidance.** Still the biggest known
   content gap. The prompt has no information about what dBFS
   represents in practice at a MOD unit's input. Saturation,
   distortion, dynamics, level-meter, compressor, and anything where
   absolute signal level matters all need this. Gain pedals don't
   care. Asked Gianfranco for the actual numbers (nominal instrument
   level, line-vs-instrument distinction, headroom convention for
   output, whether it differs across Dwarf / Duo / DuoX / Anagram);
   he doesn't have them at hand yet. The Darkglass docs give the
   Anagram number (0 dBFS = 3.119 Vrms = 12.1 dBu) — MOD-device
   numbers still pending. Add to the prompt as a "DSP design notes
   for MOD devices" section once we have the numbers.

2. **modgui (custom pedal face) support.** Strategically MOD's
   specific product differentiator inside the shared ecosystem —
   Anagram uses its own LVGL UI, modgui is what makes MOD devices
   look like MOD devices on a screen. Tricky problem: an AI can't
   see what its generated CSS produces, so improvising pedal faces
   is unreliable. Plan: a small library of well-designed pedal-face
   templates the AI selects from and customizes (knob labels,
   parameter mapping) rather than generating from scratch. Open
   design question, given the path-2 rollback: where does modgui
   live if not in a project? Possible answers — heavier `.mk`
   recipes that embed the modgui HTML/CSS too (size-limited but
   workable for templated assets), or modgui as a feature of the
   future `mod-plugin-studio` rather than the cookbook. Not yet
   decided.

3. **More example shapes still valuable.** Two examples (gain,
   ce2-chorus) cover callback-only and delay-based DSP. Future
   additions that would teach the AI new patterns: a one-pole
   filter (covers filter coefficient math), a stereo plugin
   (covers multi-channel processing), an envelope follower /
   dynamics plugin (covers per-sample envelope tracking and gain
   reduction). The centre-filter from ChatGPT could be polished
   into an example if Gianfranco wants to attribute it to himself.

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
- When an "Open gap" gets resolved, move it out of the list and into
  the historical record, or just delete it if it's no longer
  relevant. The list should always reflect what's actually open.
