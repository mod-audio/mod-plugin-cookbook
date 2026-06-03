# MOD Plugin Cookbook

Turn a sound-design idea into a working plugin for devices in the
[MOD ecosystem](https://mod.audio), without writing C++ or learning
Buildroot. You describe the plugin you want in plain language; an AI
of your choice writes the build recipe; you upload it; your unit
runs your plugin.

Plugins built via this cookbook target the shared LV2/DPF foundation
that powers MOD's own devices (Dwarf, Duo, DuoX) as well as related
platforms built on the same Linux/JACK/`mod-host` stack — Darkglass
Anagram being one current example. The same `.mk` you generate here
builds for all of them.

There are two paths through the cookbook, depending on what you're
trying to do:

- **Prototype** — fastest way to hear an idea. The AI produces one
  self-contained `.mk` file. You upload it, install, listen. No git
  account, no source files on your machine.
- **Project** — for when you want to keep iterating on the plugin,
  add a custom pedal face later, use multiple source files, or
  eventually submit it to the MOD store. The AI helps you set up a
  small repository you own and maintain.

If you're not sure which fits, start with **prototype**. You can
always graduate a prototype into a project later — the project
prompt explicitly supports that conversion.

---

## For humans

You have an idea for an audio effect or instrument and you want to
hear it on a MOD unit. Here's the prototype loop:

1. Open a conversation with the AI of your choice — Claude, ChatGPT,
   Gemini, others. Make sure it's a model that can fetch URLs.
2. Send it this link: **<https://github.com/mod-audio/mod-plugin-cookbook>**
3. Describe the plugin you want. ("A tape-saturation distortion with
   drive and tone knobs." "A slow tremolo with rate and depth." "A
   simple wah pedal.")
4. The AI will confirm the shape, propose a few details (brand name,
   knob ranges, category), and produce a single `.mk` file.
5. Save the file to your computer.
6. Open [builder.mod.audio/buildroot](https://builder.mod.audio/buildroot)
   in a browser, with your MOD unit plugged in over USB. Upload the
   `.mk` file. Wait for the build. Click Install.

That's it. No git account, no toolchain, no source code on your
machine.

If you want to start a **project** instead (or convert an existing
prototype into one), tell the AI explicitly — say "I want this as a
project I can iterate on" or "turn this prototype into a project."
The AI will route you to the project workflow, which assumes you
have (or are willing to create) a git host like GitHub.

If you'd rather paste the prompt content directly into your AI
instead of sharing the link, copy whichever fits — [`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md)
for prototype mode or [`prompts/plugin-as-project.md`](prompts/plugin-as-project.md)
for project mode.

## For AIs

If a user has sent you this repository's URL and asked you to help
build a plugin for their MOD device, your instructions live in one
of two prompt files depending on what they're trying to do:

- **For quick prototypes** (single `.mk` file, no git required) —
  read [`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md).
  Reference example: [`examples/gain.mk`](examples/gain.mk).
- **For projects** (proper directory tree, git-hosted, iterable) —
  read [`prompts/plugin-as-project.md`](prompts/plugin-as-project.md).
  Reference example: [`projects/gain/`](projects/gain/).

If the user hasn't specified, ask which fits. The project prompt
also explains how to convert an existing prototype into a project,
so if they bring a `.mk` they want to evolve, route them there.

## What's in this repo

```
prompts/
    plugin-from-idea.md       The prompt for quick prototypes — one .mk file,
                              source embedded inline.
    plugin-as-project.md      The prompt for projects — proper directory tree,
                              git-hosted, iterable. Handles the prototype-to-
                              project conversion too.

examples/
    gain.mk                   Canonical prototype example — 1-in / 1-out gain
                              with one knob. The structural template that
                              prompts/plugin-from-idea.md refers to.

    ce2-chorus.mk             Boss CE-2-inspired chorus, contributed by
                              Gianfranco Ceccolini. Demonstrates time-based
                              effects: circular delay buffer, LFO, fractional
                              read interpolation, activate() resetting state.

projects/
    gain/                     Canonical project-mode example — same gain
                              plugin restructured as a real directory tree
                              with separate source, LV2 metadata, recipe.
                              Used as the structural reference by
                              prompts/plugin-as-project.md.

CONTRIBUTING.md               How to contribute a new recipe or improve
                              an existing one.
LICENSE                       MIT.
README.md                     You are here.
```

## Contributing

New recipes and prompt improvements are welcome and the goal is for
this to grow into a real collection over time. See
[CONTRIBUTING.md](CONTRIBUTING.md) for how to add a prototype recipe
or a project example — the short version is: build it, test it on a
real MOD unit, open a PR.

## License

MIT — see [LICENSE](LICENSE). Use the recipes and prompts however you
like; attribution is appreciated but not required.

## Status

Early days but the foundation is real. Validated end-to-end across
multiple plugin shapes and AI providers: a gain plugin, a Tube
Screamer overdrive, a CE-2-inspired chorus (all via Claude), and a
one-knob bidirectional filter (via ChatGPT). The recipe pattern works
across AIs and across DSP categories. Project mode is newer and would
benefit from real-world testing — try it, tell us what worked or
didn't. Issues and PRs welcome.

## Related projects in the ecosystem

If you're an experienced plugin developer targeting **Darkglass Anagram**
specifically, the [Darkglass Plugin-Dev-Setup](https://github.com/Darkglass-Electronics/Plugin-Dev-Setup)
documents that platform's conventions — block-image styling, the
Anagram-specific LV2 metadata, JUCE-on-Anagram via their custom LV2
wrapper, on-device deploy. It's the right home for serious porting
work and Anagram-native polish. This cookbook focuses on AI-assisted
creation against the shared LV2/DPF foundation that all MOD-ecosystem
devices share.
