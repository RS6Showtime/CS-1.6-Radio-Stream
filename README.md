A Counter-Strike Mod that allows you to listen to Online Radio stations (also known as radio streams).

Because the project was originally made for the latest version of this game:
```
- Protocol version 48
- Exe version 1.1.2.7 (cstrike)
- Exe build: 19:53:27 Aug  3 2020 (8684)
```

Other versions won't work and will require searching for the offsets to specific Engine Functions manually.

This project only supports the 32-bit version, because this is also the compilation architecture of the game.

# Commands

```
radio -> Show you available commands (like vol/play/stop)
```

```
radio vol <val> -> Will set the value between 0-100 for your current stream
```

```
radio play "<url>" -> Will attempt to connect to a radio stream and play for you.
```

```
radio stop -> Will stop the current stream forever.
```

# Un4Seen (Non-Comercial use)

BASS is an audio library for use in software on several platforms. Its purpose is to provide developers with powerful and efficient sample, stream (MP3, MP2, MP1, OGG, WAV, AIFF, custom generated, and more via OS codecs and add-ons), MOD music (XM, IT, S3M, MOD, MTM, UMX), MO3 music (MP3/OGG compressed MODs), and recording functions. All in a compact DLL that won't bloat your distribution.
C/C++, Delphi, and Visual Basic APIs are provided, with several examples to get you started. .NET and other APIs are also available.

BASS is also available for the UWP platform, and ARM64 Windows.

https://www.un4seen.com/
