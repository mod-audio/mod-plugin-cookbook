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
2. AI reads `prompts/plugin-from-idea.md` (or `plugin-as-project.md`
   for project-mode), asks the user a few structured questions,
   produces either a single self-contained Buildroot `.mk` file
   (path 1) or a small project tree pointed at by a thin `.mk`
   (path 2).
3. User uploads the `.mk` at
   [https://builder.mod.audio/buildroot](https://builder.mod.audio/buildroot)
   with a unit connected over USB. Plugin builds, installs, runs.

The cookbook is the lighter-weight cousin of `mod-plugin-studio` (a
separate private project): the studio is the upcoming successor to
`mod-cloud-builder`; the cookbook works against the existing service.
Both serve MOD's broader strategic role — see "Strategic context for
the project" below.

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

## License

MIT throughout. We accept MIT-compatible contributions only. Be
deliberate about adding any dependency or referenced library that
isn't permissively licensed.

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

## Repo layout

```
README.md                Dual-audience entry point. Describes the
                         two paths and routes humans / AIs to the
                         right prompt.
LICENSE                  MIT.
CONTRIBUTING.md          How community members add recipes and
                         project examples.
CLAUDE.md                This file. Session continuity.
prompts/
    plugin-from-idea.md  Path 1 — quick prototype, single .mk file
                         with embedded source.
    plugin-as-project.md Path 2 — proper project, git-hosted, with
                         the prototype-to-project graduation flow.
examples/
    gain.mk              Path 1 canonical example. Validated on
                         real hardware.
    ce2-chorus.mk        Path 1 example contributed by Gianfranco,
                         demonstrates time-based DSP.
projects/
    gain/                Path 2 canonical example. Same gain plugin
                         as examples/gain.mk but structured as a
                         real project tree. Recipe points at the
                         cookbook repo itself as its _SITE so the
                         demo is a working buildable demo.
```

## Decisions locked in

- **One canonical entry point** — the repo root README. Both humans
  and AIs land there; the README routes them to the right prompt
  based on which path fits.
- **Two paths, sharply distinguished** — path 1 (prototype) is one
  embedded-source `.mk`; path 2 (project) is a proper directory
  tree pointed at by a thin `.mk`. Path 2 explicitly supports
  graduating a path 1 prototype into a project.
- **AI-agnostic prompts** — both prompts work with any AI that can
  fetch URLs and produce text. The path 2 prompt has two delivery
  modes built in: Mode A (filesystem-capable AIs like Codex /
  Claude Code / Cowork — AI writes files directly) and Mode B
  (chat-only AIs — AI gives code blocks the user saves manually).
- **GitHub-first, git-agnostic** — the path 2 prompt walks users
  through GitHub since that's where the community is, but the
  recipe's `_SITE` accepts any reachable git URL (GitLab, Codeberg,
  self-hosted).
- **DPF as the framework** — every plugin in the cookbook is
  DPF-based. Already on the build container, already used by all
  existing MOD skeletons, abstracts most LV2 complexity into one
  `Plugin` subclass.
- **Hand-written LV2 TTL files** — DPF's `lv2_ttl_generator` cannot
  run cross-compiled to ARM in the MOD builder image. Both paths
  hand-write `manifest.ttl` and `<bundle>.ttl`. The same constraint
  applies in both paths.
- **Embedded source pattern (path 1)** — prototype recipes embed
  DSP code and LV2 metadata inline via `define ... endef` make
  variables exported into the shell environment.
- **Repo-pointing pattern (path 2)** — project recipes point at the
  user's git repo via `_SITE`. The `recipe/<plugin>.mk` file is
  ~25 lines, no heredoc nesting.
- **`urn:mod-cookbook:<bundle>` LV2 URI convention** — for plugins
  produced via the cookbook prompts. Users with their own brand can
  use their own URI scheme.
- **`MOD Cookbook` as default brand** — but the prompt *explicitly*
  offers the user the option to use their own name or alias if
  they're publishing under their own brand. This matters for
  community ownership.

## Current state (last updated 2026-06-02)

**Path 1 validated and shipped to the community**

- Path 1 cookbook was posted to [forum.mod.audio](https://forum.mod.audio).
  Reception was good. Non-coders particularly enjoyed the "pull a
  plugin out of thin air" experience.
- Validated end-to-end with four plugins built and installed on a
  Dwarf, across Claude and ChatGPT: gain (`examples/gain.mk`),
  tube screamer (Claude Chat, one-line prompt), CE-2 chorus
  (`examples/ce2-chorus.mk`, contributed by Gianfranco), and a
  one-knob bidirectional filter (ChatGPT).
- ChatGPT initially planned to produce a regular LV2 source tree but
  corrected itself after reading the cookbook — meaningful evidence
  that the docs are doing real work.

**Path 2 built, awaiting hardware validation**

After community feedback identified two natural next directions
(custom UI / modgui and project / collaboration mode), Gianfranco
chose project mode first — cramming UI into the single-`.mk` pattern
would be a nightmare, and project mode is the architectural
foundation that eventually unlocks modgui anyway.

Path 2 is now in place:
- `prompts/plugin-as-project.md` — the project-mode prompt. Handles
  filesystem-capable AIs (Codex / Claude Code / Cowork) writing
  files directly, and chat-only AIs (Claude Chat / ChatGPT / Gemini)
  producing code blocks for the user to save. Includes a graduation
  workflow for converting a path 1 prototype to a path 2 project.
- `projects/gain/` — the canonical project-mode example, same DSP
  as `examples/gain.mk` but restructured as a real directory tree.
  The recipe points at the cookbook repo itself, so the demo is
  buildable directly from the cookbook.
- README updated to route between paths.
- CONTRIBUTING updated to cover project-mode contributions.

**Immediate next step: validate path 2 on real hardware.**
Upload `projects/gain/recipe/gain.mk` at builder.mod.audio with a
MOD unit connected. Confirm: build succeeds, plugin installs,
behaves identically to `examples/gain.mk`. If something fails, the
log tells us what to fix before any community testing.

**Open gaps tracked here, in rough priority order**

1. **MOD device signal-level guidance.** Still the biggest known
   content gap. The prompts have no information about what dBFS
   represents in practice at a MOD unit's input. Saturation,
   distortion, dynamics, level-meter, compressor, and anything where
   absolute signal level matters all need this. Gain pedals don't
   care. Asked Gianfranco for the actual numbers (nominal instrument
   level, line-vs-instrument distinction, headroom convention for
   output, whether it differs across Dwarf / Duo / DuoX / Anagram);
   he doesn't have them at hand yet. Add to the prompts as a "DSP
   design notes for MOD devices" section once we have the numbers.

2. **modgui (custom pedal face) support.** The other community-asked
   direction, *and* strategically MOD's specific product differentiator
   inside the shared ecosystem — Anagram uses its own LVGL UI, modgui
   is what makes MOD devices look like MOD devices on a screen. Plan:
   a small library of well-designed pedal-face templates that the AI
   selects from and customizes (rather than generating CSS from
   scratch, which would be unreliable since the AI can't see what it
   produces). Fits naturally into path 2 once path 2 is validated —
   adds a `modgui/` subdirectory inside the project. Single-`.mk`
   mode would be too cramped for modgui assets so this stays
   project-mode only. Gianfranco has flagged this as the most
   urgent next investment after path 2 hardware validation.

3. **More example shapes still valuable.** Two prototype examples
   (gain, ce2-chorus) and one project example (gain) cover the
   basics. Future additions that would teach the AI new patterns: a
   one-pole filter (covers filter coefficient math), a stereo plugin
   (covers multi-channel processing), an envelope follower / dynamics
   plugin (covers per-sample envelope tracking and gain reduction).
   The centre-filter from ChatGPT could be polished into an example
   if Gianfranco wants to attribute it to himself.

4. **Path 2 validation in the community.** Once we've confirmed
   `projects/gain/` builds on real hardware, the path 2 announcement
   should be a separate, smaller forum post (or addition to the
   original one). Same kind of "try it and tell us what worked"
   framing as path 1's launch.

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
