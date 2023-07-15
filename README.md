# Sqeleton

[![CI]](https://github.com/redtide/qruler/actions/workflows/build.yml)

Qt application template repository.

See the related [website page] for further information.

## Features

- Resource management following the Freedesktop [Desktop Entry] Specification
  file naming convention (icons, desktop and appdata files)
- [Appstream] metadata information
- Locale translations via [LXQt build tools]
- Install step

## Dependencies

Under Debian based systems:

- cmake (build only)
- qtbase5-dev
- qttools5-dev (build only)

## Build

First time download:

```bash
git clone --recurse-submodules https://github.com/qtilities/qruler.git
```

Get missing `lxqt-build-tools` submodule:

```bash
git submodule update --init --recursive
```

then:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build
```

## Licenses

- Sqeleton is licensed under the [MIT] license.
- Application icon is from [Openclipart], [CC0-1.0] license.


[Appstream]:        https://freedesktop.org/software/appstream/docs/chap-Quickstart.html
[CC0-1.0]:          https://creativecommons.org/publicdomain/zero/1.0/
[CI]:               https://github.com/redtide/qruler/actions/workflows/build.yml/badge.svg
[Desktop Entry]:    https://specifications.freedesktop.org/desktop-entry-spec/latest/ar01s02.html
[LXQt build tools]: https://github.com/lxqt/lxqt-build-tools
[MIT]:              COPYING
[Openclipart]:      https://openclipart.org/
[website page]:     https://qtilities.github.io/sqeleton/
