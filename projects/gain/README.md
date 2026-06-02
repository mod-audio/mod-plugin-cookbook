# Gain (project-mode example)

A simple 1-in / 1-out mono gain plugin with a single 0–4× knob.
Same DSP as [`examples/gain.mk`](../../examples/gain.mk), but
structured as a proper project — the C++ source, LV2 metadata, DPF
wrapper, and Buildroot recipe each live in their own file.

This is the canonical worked example for the path 2 workflow described
in [`prompts/plugin-as-project.md`](../../prompts/plugin-as-project.md):
a plugin that you can iterate on over time, keep in version control,
extend with more files, and eventually add a custom pedal face to.

## Layout

```
gain/
├── plugin/
│   ├── Plugin.cpp            the DSP
│   ├── DistrhoPluginInfo.h   plugin metadata (brand, name, URI, ports)
│   └── Makefile              DPF wrapper (build with `make lv2_dsp`)
├── lv2/
│   ├── manifest.ttl          hand-written; pointed at by Buildroot's install step
│   └── plugin.ttl
├── recipe/
│   └── gain.mk               the Buildroot recipe to upload at builder.mod.audio
└── README.md                 you are here
```

## Build flow

The `recipe/gain.mk` file points at this repository as its `_SITE`.
When uploaded to [builder.mod.audio/buildroot](https://builder.mod.audio/buildroot),
the builder fetches the cookbook, builds `plugin/` against DPF, and
installs the bundle (with the hand-written `.ttl` files from `lv2/`).

## Iteration loop for your own plugin

Once you've forked or copied this structure into your own repository:

1. Edit `plugin/Plugin.cpp` (or `DistrhoPluginInfo.h` or `lv2/*.ttl`)
   to change what the plugin does.
2. `git commit && git push`.
3. Update `recipe/<your-plugin>.mk` to point at your new commit
   (`_VERSION = <new-sha-or-tag>`).
4. Re-upload that `.mk` at `builder.mod.audio/buildroot`. Install.
5. Hear the change on the unit.

The `.mk` file is small enough that step 3 is usually just changing
one line.

## Why hand-written TTL files

DPF normally generates the LV2 `.ttl` metadata by running a small
native helper against the compiled `.so`. That helper can't run when
the build is cross-compiled to the MOD's ARM target. So this project
hand-writes `manifest.ttl` and `plugin.ttl` and the recipe copies them
into the final bundle. If you add or change a parameter in the C++,
remember to keep the `.ttl` files in sync.
