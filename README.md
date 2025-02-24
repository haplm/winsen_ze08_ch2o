# Support for Winsen ZE08-CH2O in ESPHome

This is a simple external component (as required by ESPHome 2025.2 and later) enabling use of Winsen ZE08-CH2O in ESPHome / Home Assistant.

It is based on the code published here: https://gist.github.com/cretep/f96606dc6a4eae0d85993d6085959220

How to use it:
1. The component needs to reside inside the ESPHome configuration directory (where you have your YAML definitions for your ESPHome devices). In my case, I have created a new directory `components`, where I have placed the directory `ze08_ch2o` (and its content). Full path is then `config/esphome/components/ze08_ch2o`
2. Insert the snippet in `sample_config.yaml` into your YAML definition, and adapt as needed
3. Install the YAML (ie. compile everything), hopefully there are no issues

If anyone has the skill to adapt this into a regular ESPHome component, please feel free to do it
