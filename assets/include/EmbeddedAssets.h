#pragma once

#include "derive/assets/EmbeddedAsset.h"
#include <map>
#include <string>

#include "buggyriv.h"
#include "deriveiconpng.h"
#include "juiceriv.h"

namespace derive {
	namespace assets {

		class EmbeddedAssets {
		public:
			std::map<std::string, derive::assets::EmbeddedAssetData> items = {
				{ "buggy.riv", buggyriv },
				{ "derive-icon.png", deriveiconpng },
				{ "juice.riv", juiceriv },
			};
		};

	}
}