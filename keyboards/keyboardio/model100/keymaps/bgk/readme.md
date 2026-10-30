# bgk keymap for the Keyboardio Model 100

Port of my Kaleidoscope sketch (`Model100`) to QMK.

## Layers

| Layer      | Reached by                                         |
|------------|----------------------------------------------------|
| `QWERTY`   | Default base layer                                 |
| `COLEMAK`  | Base layer (Colemak-DH), selected from `LAYSEL`    |
| `GAME`     | Base layer for gaming, selected from `LAYSEL`      |
| `NUMPAD`   | Toggled from the top right key                     |
| `GAMEFCN`  | Palm keys while `GAME` is the base layer           |
| `FUNCTION` | Left palm key                                      |
| `ARROW`    | Right palm key (window/wezterm shortcuts)          |
| `LAYSEL`   | Right palm on `FUNCTION`/`ARROW`, or one-shot key  |

`LAYSEL` holds the base layer switches (left hand `Q`/`W`/`E` positions) and
the Danish letters æ, ø and å (right hand `J`/`K`/`L` positions).

## Behaviour carried over from Kaleidoscope

* One-shot modifiers with a 1 s timeout; Escape cancels pending one-shots.
* Tap dances with a 200 ms timeout (`:`/`;`, `-`/`_`, copy/paste, wezterm,
  lock/Ctrl+Alt+Del).
* Æ/Ø/Å are typed as compose sequences on Right Alt, so the host needs a
  compose key there (e.g. WinCompose on Windows).
* Held modifiers and pending one-shots are highlighted, and Caps Lock /
  Num Lock light the Tab / Esc keys.
* The Kaleidoscope colormap (`tools/colormap/colormap.txt` with the
  `pastel` palette) is drawn from `rgb_matrix_indicators_advanced_user`: each
  layer has its own per-key colours and the map of the highest active layer
  is shown, with the mod and lock highlights on top. RGB Matrix is forced on
  at boot and the keyboard's animations are compiled out. Palette colours
  are used as-is.

Not ported: the password macros (those two keys on `ARROW` do nothing) and
the unused macros/tap dances.

## Flashing

`PROG` is Escape in this keymap. Hold it while plugging in the keyboard to
enter the bootloader.
