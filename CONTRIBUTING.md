# Contributing to the MOD Plugin Cookbook

The whole point of this repo is to grow into a real collection of
recipes. Pull requests are not just welcome — they're the funnel. If
you've built something on builder.mod.audio that works, sending it
here is the move.

## What makes a good contribution

**A new prototype recipe** — a `.mk` file under `examples/`
implementing a plugin idea that isn't already covered. Anything is
fair game: an overdrive, a delay, a wavefolder, a step sequencer, a
wah, a synth voice, a utility tool. The shape doesn't matter, the
audio result does. These follow the embedded-source pattern in
[`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md).

**A new project example** — a directory under `projects/<plugin-name>/`
following the structure in [`projects/gain/`](projects/gain/) and
[`prompts/plugin-as-project.md`](prompts/plugin-as-project.md). Most
useful when the plugin would be awkward as a single-file recipe —
multi-file DSP, a custom pedal face once we add that support, or
just a polished example others can fork as a starter.

**An improvement to an existing recipe or project** — fixing a bug,
tightening DSP, adding a parameter that makes it more musically
useful. Document what changed and why in the PR description.

**A new prompt under `prompts/`** — if you've found another problem
the cookbook should help solve. We currently have prompts for
"idea → prototype" and "idea or prototype → project." Future ones
might cover explaining a build failure, designing a modgui pedal
face, or porting an existing LV2 plugin from its native build
system.

**Documentation improvements** — clearer wording, better examples,
fixing rough edges in the prompts, the README, or any project's
own README. Small PRs are very welcome.

## Hard requirements for a new recipe or project

Before opening the PR, your contribution must:

1. **Build successfully** at
   [https://builder.mod.audio/buildroot](https://builder.mod.audio/buildroot).
2. **Install and run on a real MOD unit** (Dwarf, Duo, DuoX, or
   Anagram). Confirm parameters respond, no crackles or instability,
   no clipping at sensible default settings.
3. **Follow the cookbook schema** — prototype recipes follow the
   embedded-source pattern in
   [`prompts/plugin-from-idea.md`](prompts/plugin-from-idea.md);
   projects follow the directory structure in
   [`prompts/plugin-as-project.md`](prompts/plugin-as-project.md)
   and the canonical [`projects/gain/`](projects/gain/) example.
4. **Be MIT-licensed (or MIT-compatible)** — you wrote it, or you
   have permission to relicense it. The cookbook is MIT throughout
   and we keep it that way.
5. **Not be a duplicate** of something already in `examples/` or
   `projects/`. A substantially different take on an existing idea
   (e.g. a second overdrive with different DSP) is fine — say so in
   the PR description and pick a distinct filename/directory name.

## How to submit a prototype recipe

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

## How to submit a project example

Similar process but the contribution is a directory rather than a
single file:

1. Fork this repo.
2. Create `projects/<your-plugin-name>/` following the layout of
   [`projects/gain/`](projects/gain/) — `plugin/`, `lv2/`, `recipe/`,
   plus the project's own `README.md`, `LICENSE`, and `.gitignore`.
3. The recipe at `projects/<your-plugin-name>/recipe/<your-plugin-name>.mk`
   can point at either the cookbook itself (like the `projects/gain/`
   example does — useful for projects meant to live within the
   cookbook) or at a separate git repository you maintain (for
   projects that have their own life outside the cookbook). Either is
   acceptable.
4. The project's `README.md` should describe what the plugin does,
   its DSP shape, and the iteration loop.
5. Open a pull request with the same kind of testing notes as for a
   prototype recipe.

## Norms

- **One recipe or project per PR.** Easier to review, easier to roll
  back if something turns out to be subtly broken.
- **Tested on hardware.** This isn't negotiable. The whole point of
  the cookbook is that things work; an untested contribution is
  worse than no contribution because it wastes the next user's time.
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
