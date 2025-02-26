# CapibaraZero firmware

<img src="https://github.com/CapibaraZero/.github/blob/main/logo.png?raw=true" width="256" />

---

## ANNOUNCEMENT: Now CapibaraZero is available for SBC that runs Linux(Raspberry Pi, OrangePi, ...). [Here](https://github.com/CapibaraZero/fw_linux) you can find more information.

CapibaraZero aim to be a cheap alternative to FlipperZero™. It's based on ESP32 boards especially on ESP32-S3 but we want to port firmware to all ESP family boards.

This repo contains the main firmware that make capibaraZero works.

Most of attacks are separated in repository to isolate them from GUI to make project structure more readable.

Docs: https://capibarazero.github.io/docs/

## Build firmware

To build project just must have PlatformIO installed and a working version of GNU Bison and Flex

Before building project you must execute init_libs.sh to prepare PN532 libs

```bash
bash init_libs.sh   # Init NFC and Duktape libs
pio run
# To upload firmware
pio run -t upload
```

[You can use the precompiled firmware from releases](https://github.com/CapibaraZero/fw/releases)

## Status

The project is BETA! 🎉

Working Features:

- Wi-Fi support
- BLE support
- BadUSB support
- NFC support
- Some network attacks
- SubGHZ(Beta support, need more testing)
- IR(repeat support is not ready but most of the signals will works)

More details in the project view: https://github.com/orgs/CapibaraZero/projects/2/views/1

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

If you wanna port project to other ESP boards, we have made a little guide here: https://capibarazero.com/docs/development/porting_to_others_boards/new_porting

## Social

- [Matrix server](https://matrix.to/#/#capibarazero:capibarazero.com)
- [Discord-Matrix bridge](https://discord.gg/77f3BHvnhf)

## License

[GPL-3](https://www.gnu.org/licenses/gpl-3.0.html)
