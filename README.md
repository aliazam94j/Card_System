# Card System

A simulated card-based access control system, built in C. Think of it as the
software behind a keycard door reader — add or remove a card's access, scan a
card to check if it opens the door, and everything persists to disk so the
card list survives between runs.

This was a school assignment, but I went back into it later to fix real
issues found during a code review — a couple of them (a header declared but
never implemented, a linker error from building the wrong way) taught me more
about how multi-file C projects actually fit together than the original
assignment did.

## What it does

```
   Admin menu       |
1. Remote open door  |
2. List all cards    |
3. Add/remove access |
4. Exit              |
9. FAKE TEST         |
```

- **Remote open door** — simulates a door unlock with a timed delay.
- **List all cards** — shows every card in the system: number, access status, date added.
- **Add/remove access** — enter a card number; if it exists, grant/deny/delete it, otherwise it gets added as a new card.
- **Fake test** — simulates scanning a card and reports whether it would open the door.
- Cards persist to `cards.dat` (a binary file) between runs, loaded on startup and saved on exit.

## Project structure

| File | Responsibility |
|---|---|
| `main.c` | Menu loop, ties everything together |
| `card.c` / `card.h` | The `Card` struct and how to print one |
| `cardfunction.c` / `cardfunction.h` | Core logic — add/remove access, scanning, save/load |
| `systemstate.c` / `systemstate.h` | Owns the dynamic card list (init/free) |
| `safeinput.c` / `safeinput.h` | Input parsing that rejects bad input instead of crashing |
| `menu.c` / `menu.h` | Just the menu text |

## Build

Built with a Makefile against the MinGW-w64 toolchain.

```powershell
mingw32-make
.\main.exe
```

## What I learned

- Dynamic arrays in C — growing the card list with `realloc` as it fills up, doubling capacity instead of reallocating one at a time.
- Persisting structs to disk directly with `fwrite`/`fread`, and loading them back on startup.
- Splitting a project across multiple `.c`/`.h` files with real separation of concerns, instead of one big file.
- Debugging a real linker error: `main.c` calling functions that "undefined reference" errors said didn't exist — turned out to be a difference between compiling one file directly versus building through the Makefile, which links every source file together. Multi-file C projects can compile clean per-file and still fail entirely at the link step.
- Why header include guards matter, and why they should never start with a double underscore (that namespace is reserved for the compiler).

## Where this could go

Right now this is a pure software simulation — the "door," the "scanner," and
the "lamp" are all just `printf` statements. A natural next step would be
moving it onto real hardware: an RFID/NFC reader (e.g. an RC522 module) for
actual card scans instead of typing a number, a relay to trigger a real door
lock, and an LED (or the lamp logic already in `remoteOpenDoor`) wired to a
real GPIO pin instead of printed text. A microcontroller like the Pico or an
ESP32 could own the scanner/lock/LED side and talk to this same access logic
underneath — the card storage and access rules wouldn't need to change much,
just what's sending scans in and what's receiving "granted"/"denied" out.

## Fixed during review

A few things a fresh look turned up, since fixed:
- `initSystemstate`/`freeSystemstate` were declared in `systemstate.h` but never implemented — `main.c` was duplicating that logic inline instead.
- The compiled binary and object files were committed to git instead of being ignored.
- Card numbers had no validation — negative numbers or zero were silently accepted as valid new cards.
