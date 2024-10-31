# Quantum Mechanical Keyboard Firmware

This is the branch where my personal keymaps lives. Remember to keep the master branch clean, so it is easier to sync with upstream qmk

## Dactyl manuform
Keymap can be found at `keyboards/handwired/dactyl_manuform/5x7/keymaps/bgk/`

Compile like this
```
qmk compile -kb handwired/dactyl_manuform/5x7 -km bgk
```

Flash each half with this command
```
qmk flash -kb handwired/dactyl_manuform/5x7 -km bgk
```

## Ergodox infinity
Keymap can be found at `keyboards/input_club/ergodox_infinity/keymaps/bgk/`

Compile like this
```
qmk compile -kb input_club/ergodox_infinity -km bgk
```

Flash each half with this command
Untested command !!!!!!!!
```
qmk flash -kb input_club/ergodox_infinity -km bgk
```


# Preonic UNTESTED commands and does not compile
Keymap can be found at `keyboards/preonic/keymaps/bgk/`

Compile like this
```
qmk compile -kb preonic -km bgk
```

Flash each half with this command
```
qmk flash -kb preonic -km bgk
```

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
