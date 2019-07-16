// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>
#include <initializer_list>

namespace CryptoNote {
	struct CheckpointData {
		uint32_t index;
		const char* blockId;
	};

	const std::initializer_list<CheckpointData> CHECKPOINTS = {
		{        0, "4755c750a1ed8535ba1789570899720f3cd010ccf7ab70a1a2d2d53f298eafd5"  },
		{        100, "4b706615609647fa3a224ea902424a5bdba5e4717d9d8935fa477022694f3351"  },
		{        200, "a37e077202b13f0e4c052ef3cb413d729dc843f592236e636e48b6bced55549a"  },
		{        300, "5c274464d104c22e395d694cd8b466ad47ccae143c31ac5f5feccc0d7b95a149"  },
		{        400, "b91c7d0b7f86c0677030abf2067791cb9d80be25a4c86b36b9d346ef95b9f979"  },
		{        500, "942747b58ef97bccf45a0985e46fbec00aa6a3931f1f9ab6b179c4bf370274d5"  },
		{        600, "3c8d432203a64e90ebde3469857be5c9943d64c378af310ff4b371f8e52a2288"  },
		{        700, "2253901ffd699e5ba4c5f7bda9906415c155ce829e8b3837527aeb70327cbe48"  },
		{        800, "1001ab4a43ec0e41d0b4e97d876a2c3008a39518c917cd16e570e875f83b0523"  },
		{        900, "d5b8b793cdb7af0780f4a53c7a64fc1ab93108d8cebbcf903519b80c047178d1"  },
		{        1000, "da5ff36c3741f00b071b226d20d6598fb72b43fa81adfeb400bda5a3151c7f6a"  }
	};
}
