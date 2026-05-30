# MOD Plugin Cookbook

Recipes and AI prompts for turning a sound-design idea into a working
plugin for [MOD devices](https://mod.audio), without learning Buildroot
or LV2 first.

## Who this is for

People who have an idea for an audio effect or instrument and would like
to hear it running on a MOD unit — but who don't necessarily write C++,
don't want to set up a cross-compile toolchain, and don't want to learn
the LV2 metadata format. If you're an experienced LV2 / DPF / JUCE
developer with your own build pipeline, you don't need this; the
[MOD Online Builder](https://builder.mod.audio) accepts hand-written
Buildroot recipes directly.

## How it works

The [MOD Online Builder](https://builder.mod.audio) (see its `/buildroot`
route) accepts a single `.mk` file — a Buildroot package makefile — and
produces a compiled `.lv2` plugin bundle which you can install on a MOD
unit connected to your computer over USB.

A `.mk` file is normally a build recipe pointing at source code in a git
repository. The recipes in this cookbook do something more interesting:
they *embed the plugin's entire source* — C++ DSP code, LV2 metadata,
and the framework wrapper — directly inside the makefile, as text written
out by `printf` at build time. The dev never needs a git account, never
needs to push code anywhere; the single `.mk` file is the entire
deliverable.

That makes the whole flow paste-friendly. An AI generates a `.mk` file
from your description, you download it, you upload it to
`builder.mod.audio`, you install. End to end, no other accounts or tools.

## What's in here

```
mod-plugin-cookbook/
├── prompts/
│   └── plugin-from-idea.md     Paste this into your AI of choice
│                               (Claude, ChatGPT, Gemini, …) and tell it
│                               about the sound you want to build.
│
└── examples/
    └── gain.mk                 The canonical worked example —
                                a 1-in / 1-out gain plugin with one
                                knob. Validated end-to-end on the live
                                builder. The prompt references this as
                                its reference pattern.
```

## Using a prompt

1. Open the prompt file (e.g. [`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md)).
2. Paste its contents into a fresh conversation with the AI of your
   choice.
3. Describe the plugin you want, in plain language. ("A tape-saturation
   distortion with drive and tone knobs.")
4. The AI replies with a `.mk` file. Save it to your computer.
5. Open [`builder.mod.audio/buildroot`](https://builder.mod.audio/buildroot)
   in a browser, with your MOD unit connected by USB.
6. Upload the `.mk`. Wait for the build. Click Install.

## Contributing

Pull requests welcome — new prompts, new worked examples, fixes to the
existing ones. A new recipe is a great PR. A new prompt that solves a
genuinely different problem (debugging a build failure, designing a
modgui pedal face) is also welcome.

When contributing an example `.mk`, please validate it end-to-end on
`builder.mod.audio` against a real MOD unit before opening the PR.

## License

MIT — see [LICENSE](LICENSE). Use the recipes and prompts however you
like; attribution is appreciated but not required.

## Status

This is an early, evolving collection. Expect it to grow as the
community builds more recipes and as MOD's own tooling matures.
