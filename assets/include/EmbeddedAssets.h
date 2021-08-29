#pragma once

#include "derive/assets/EmbeddedAsset.h"
#include <map>
#include <string>

#include "juiceriv.h"

namespace derive {
	namespace assets {

		class EmbeddedAssets {
		public:
			std::map<std::string, derive::assets::EmbeddedAssetData> items = {
				{ "juice.riv", juiceriv },
			};
		};

	}
}