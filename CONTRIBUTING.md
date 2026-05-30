# Contributing to the MOD Plugin Cookbook

The whole point of this repo is to grow into a real collection of
recipes. Pull requests are not just welcome — they're the funnel. If
you've built something on builder.mod.audio that works, sending it
here is the move.

## What makes a good contribution

**A new recipe** — a `.mk` file under `examples/` implementing a
plugin idea that isn't already covered. Anything is fair game: an
overdrive, a delay, a wavefolder, a step sequencer, a wah, a synth
voice, a utility tool. The shape doesn't matter, the audio result
does.

**An improvement to an existing recipe** — fixing a bug in a published
example, tightening DSP, adding a parameter that makes it more
musically useful. Document what changed and why in the PR description.

**A new prompt under `prompts/`** — if you've found another problem
the cookbook should help non-devs solve. The current prompt produces
a plugin from a sound idea; a future one might explain a build
failure, design a modgui pedal face, or convert an existing LV2
plugin into the embedded-source format.

**Documentation improvements** — clearer wording, better examples,
fixing rough edges in the prompt or the README. Small PRs are very
welcome.

## Hard requirements for a new recipe

Before opening the PR, your recipe must:

1. **Build successfully** at
   [https://builder.mod.audio/buildroot](https://builder.mod.audio/buildroot).
2. **Install and run on a real MOD unit** (Dwarf, Duo, DuoX, or
   Anagram). Confirm parameters respond, no crackles or instability,
   no clipping at sensible default settings.
3. **Be self-contained** — a single `.mk` file with all source
   embedded, following the schema in
   [`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md). No
   external git URLs for source other than DPF.
4. **Be MIT-licensed (or MIT-compatible)** — you wrote it, or you
   have permission to relicense it. The cookbook is MIT throughout
   and we keep it that way.
5. **Not be a duplicate** of something already in `examples/`. If
   it's a substantially different take on an existing idea (e.g. a
   second overdrive with different DSP), that's fine — say so in the
   PR description and pick a distinct filename.

## How to submit a recipe

1. Fork this repo on GitHub.
2. Put your recipe at `examples/<your-plugin-name>.mk`. The filename
   must be lowercase letters, digits, and dashes only, not starting
   with a digit. The filename (minus `.mk`) is also the LV2 bundle
   name.
3. At the top of the file, include a comment block with:
   - The license line (`SPDX-License-Identifier: MIT` and copyright).
   - A one-paragraph description of what the plugin does and how to
     drive it (typical use, what each knob feels like, anything
     non-obvious about getting good sounds out of it).
4. Open a pull request. In the PR description, please include:
   - The platform you tested on (Dwarf / Duo / DuoX / Anagram).
   - A short note on the DSP approach ("tanh waveshaping with input HP
     filter and a tone stack as one-pole LP").
   - Anything unusual the reviewer should know.
5. A maintainer will review, possibly suggest small tweaks, and merge.

## Norms

- **One recipe per PR.** Easier to review, easier to roll back if
  something turns out to be subtly broken.
- **Tested on hardware.** This isn't negotiable for recipes. The
  whole point of the cookbook is that things work; an untested recipe
  is worse than no recipe because it wastes the user's time.
- **Friendly defaults.** Pick parameter ranges and defaults that
  sound good on first load. Users may never turn knobs from the
  defaults; the plugin should already be usable as-is.
- **Be kind in review.** Most contributors will be people new to
  audio DSP, plugin development, or both. The goal is to grow the
  collection, not to gatekeep.

## License of contributed material

By submitting a PR, you agree to license your contribution under the
MIT License (see [LICENSE](LICENSE)). If your recipe draws on someone
else's code or ideas, credit them in the comment block at the top of
your file.

## Questions?

Open an issue on the repo and someone will help. If you're stuck on
the DSP itself rather than the cookbook mechanics, the
[MOD community forum](https://forum.mod.audio) is a friendly place
to ask.
