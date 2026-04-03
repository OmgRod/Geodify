import re
import json
from pathlib import Path

DIR = Path("src")
MOD_JSON_PATH = Path("Base_mod.json")
MOD_JSON_PATH_OUTPUT = Path("mod.json")
COMMENT_PATTERN = re.compile(r'//\[\[omgrod\.geodify/TAG\]\]\s*([^\s:]+)')
MACRO_PATTERN = re.compile(r'ADD_TAG\(\s*"([^"]+)"\s*\)')

#print("Looking in:", DIR.resolve())

tag_settings = {}
for file in DIR.rglob("*.cpp"):
    print(file)
    text = file.read_text()
    print(text)
    new_lines = []
    for line in text.splitlines():
        match = COMMENT_PATTERN.search(line) or MACRO_PATTERN.search(line)
        #print(f"line: {line} data : {match}")
        match = COMMENT_PATTERN.search(line)
        if not match:
            match = MACRO_PATTERN.search(line)

        if match:
            name = match.group(1)
            if "-" in name:
                before_last, after_last = name.rsplit("-", 1)
            else:
                before_last, after_last = "", name

            key = f"{before_last}/{after_last}" if before_last else after_last

            if key not in tag_settings:
                tag_settings[key] = {
                    "name": after_last.replace("_", " "),
                    "description": after_last,
                    "type": "bool",
                    "default": False
                }

        new_lines.append(line)

if MOD_JSON_PATH.exists():
    mod_data = json.loads(MOD_JSON_PATH.read_text())
else:
    mod_data = {}

mod_data.setdefault("settings", {})

new_settings = {}
inserted = False
for key, value in mod_data["settings"].items():
    if key == "other-title" and not inserted:
        for new_key, new_value in tag_settings.items():
            if new_key not in mod_data["settings"]:
                new_settings[new_key] = new_value
        inserted = True
    new_settings[key] = value

if not inserted:
    for new_key, new_value in tag_settings.items():
        if new_key not in mod_data["settings"]:
            new_settings[new_key] = new_value

mod_data["settings"] = new_settings

MOD_JSON_PATH_OUTPUT.write_text(json.dumps(mod_data, indent=4))

print(f"Processed {len(tag_settings)} tags and added new settings to mod.json")
