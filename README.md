# Geodify
A mod made to to change most menus' backgrounds to the Geode one 

<img src="logo.png" width="150" alt="Logo" />

## Building

To build this mod, follow one of the methods below:

### VS Code

1. Open the project in VS Code.
2. Install the necessary dependencies (if not already done).
3. Select the appropriate build kit for your platform. You can do this by navigating to the "CMake Tools" tab in the bottom left and selecting "Select a Kit".
4. Choose the correct kit for your environment (e.g., macOS, Windows, etc.).
5. After selecting the kit, you can build the project by clicking "Build" in the "CMake" tab or by using the terminal command:

```bash
cmake --build .
```
This will compile the mod and generate the necessary files.

### GitHub Actions

1. Push your changes to GitHub.
2. Open the repository and navigate to the Actions tab.
3. Select the workflow called "Build Geode Mod".
4. Choose the latest commit.
5. After the build is complete, download the generated artifacts from the build step to get the built mod files.

## Adding Layers

### Geometry Dash

To add a custom background layer to a **Geometry Dash** menu, follow the example below. This demonstrates how to add a background layer in `CreatorLayer`.

```cpp
#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class $modify(MyCreatorLayer, CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-creator")){
			if (auto bg = this->getChildByID("background")){
				bg->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			

			this->addChild(swelvyBG);
		}
		return true;
	}
};
```


### External Mods

For external mods that modify the background of a specific menu, you can use the following example. This shows how to hook into `GlobedLevelListLayer` to add a custom background.

```cpp
#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <alphalaneous.alphas_geode_utils/include/NodeModding.h>

using namespace geode::prelude;

SET_SWELVY(GlobedLevelListLayer, "dankmeme.globed2/GlobedLevelListLayer", "background");

```
This way is new from v2.0.0+!