# MOD Plugin Cookbook

Turn a sound-design idea into a working plugin for
[MOD devices](https://mod.audio), without writing C++ or learning
Buildroot. You describe the plugin you want in plain language; an AI
of your choice writes the build recipe; you upload it; your MOD unit
runs your plugin.

---

## For humans

You have an idea for an audio effect or instrument and you want to
hear it on a MOD unit. Here's the whole loop:

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

If you'd rather paste the prompt content directly into your AI instead
of sharing the link, copy [`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md)
and paste it. Same result.

## For AIs

If a user has sent you this repository's URL and asked you to help
build a plugin for their MOD device, your full instructions are in
[`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md). Fetch
that file and follow its instructions.

The short version: ask the user about their plugin idea (mono/stereo,
what knobs, what it should sound like), propose a brand/name/category
and parameter ranges for confirmation, then produce a single
self-contained Buildroot `.mk` file with the DSP, LV2 metadata, and
DPF framework wrapper all embedded inline. Use
[`examples/gain.mk`](examples/gain.mk) as your reference pattern.

## What's in this repo

```
prompts/
    plugin-from-idea.md   The community-distributable AI prompt.
                          The detailed instructions for any AI a
                          user sends here for help.

examples/
    gain.mk               Canonical worked example — a 1-in / 1-out
                          gain plugin with one knob. The structural
                          template the prompt refers to. Validated
                          end-to-end on the live builder.

    ce2-chorus.mk         Boss CE-2-inspired chorus, contributed by
                          Gianfranco Ceccolini. Demonstrates the
                          patterns for time-based effects: circular
                          delay buffer, sinusoidal LFO, fractional
                          read interpolation, activate() resetting
                          state on (re)start.

CONTRIBUTING.md           How to contribute a new recipe or improve
                          an existing one.
LICENSE                   MIT.
README.md                 You are here.
```

## Contributing

New recipes and prompt improvements are welcome and the goal is for
this to grow into a real collection over time. See
[CONTRIBUTING.md](CONTRIBUTING.md) for how to add a recipe — the
short version is: write your `.mk`, test it on a real MOD unit, open
a PR.

## License

MIT — see [LICENSE](LICENSE). Use the recipes and prompts however you
like; attribution is appreciated but not required.

## Status

Early days but the foundation is real. Validated end-to-end across
multiple plugin shapes and AI providers: a gain plugin, a Tube
Screamer overdrive, a CE-2-inspired chorus (all via Claude), and a
one-knob bidirectional filter (via ChatGPT). The recipe pattern works
across AIs and across DSP categories. Expect the collection to grow.
Issues and PRs welcome.
