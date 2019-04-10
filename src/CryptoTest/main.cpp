// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2019, The Plenteum Developers
//
// Please see the included LICENSE file for more information.

#undef NDEBUG

#include <iostream>
#include <chrono>
#include <assert.h>

#include <cxxopts.hpp>
#include <config/CliHeader.h>

#include "CryptoNote.h"
#include "CryptoTypes.h"
#include "Common/StringTools.h"
#include "crypto/crypto.h"

#define PERFORMANCE_ITERATIONS  1000
#define PERFORMANCE_ITERATIONS_LONG_MULTIPLIER 10

using namespace Crypto;
using namespace CryptoNote;

const std::string INPUT_DATA = "0100fb8e8ac805899323371bb790db19218afd8db8e3755d8b90f39b3d5506a9abce4fa912244500000000ee8146d49fa93ee724deb57d12cbc6c6f3b924d946127c7a97418f9348828f0f02";

const std::string CN_FAST_HASH = "b542df5b6e7f5f05275c98e7345884e2ac726aeeb07e03e44e0389eb86cd05f0";

const std::string CN_SLOW_HASH_V0 = "1b606a3f4a07d6489a1bcd07697bd16696b61c8ae982f61a90160f4e52828a7f";
const std::string CN_SLOW_HASH_V1 = "c9fae8425d8688dc236bcdbc42fdb42d376c6ec190501aa84b04a4b4cf1ee122";
const std::string CN_SLOW_HASH_V2 = "871fcd6823f6a879bb3f33951c8e8e891d4043880b02dfa1bb3be498b50e7578";

const std::string CN_LITE_SLOW_HASH_V0 = "28a22bad3f93d1408fca472eb5ad1cbe75f21d053c8ce5b3af105a57713e21dd";
const std::string CN_LITE_SLOW_HASH_V1 = "87c4e570653eb4c2b42b7a0d546559452dfab573b82ec52f152b7ff98e79446f";
const std::string CN_LITE_SLOW_HASH_V2 = "b7e78fab22eb19cb8c9c3afe034fb53390321511bab6ab4915cd538a630c3c62";

const std::string CN_DARK_SLOW_HASH_V0 = "bea42eadd78614f875e55bb972aa5ec54a5edf2dd7068220fda26bf4b1080fb8";
const std::string CN_DARK_SLOW_HASH_V1 = "d18cb32bd5b465e5a7ba4763d60f88b5792f24e513306f1052954294b737e871";
const std::string CN_DARK_SLOW_HASH_V2 = "a18a14d94efea108757a42633a1b4d4dc11838084c3c4347850d39ab5211a91f";

const std::string CN_DARK_LITE_SLOW_HASH_V0 = "faa7884d9c08126eb164814aeba6547b5d6064277a09fb6b414f5dbc9d01eb2b";
const std::string CN_DARK_LITE_SLOW_HASH_V1 = "c75c010780fffd9d5e99838eb093b37c0dd015101c9d298217866daa2993d277";
const std::string CN_DARK_LITE_SLOW_HASH_V2 = "fdceb794c1055977a955f31c576a8be528a0356ee1b0a1f9b7f09e20185cda28";

const std::string CN_TURTLE_SLOW_HASH_V0 = "546c3f1badd7c1232c7a3b88cdb013f7f611b7bd3d1d2463540fccbd12997982";
const std::string CN_TURTLE_SLOW_HASH_V1 = "29e7831780a0ab930e0fe3b965f30e8a44d9b3f9ad2241d67cfbfea3ed62a64e";
const std::string CN_TURTLE_SLOW_HASH_V2 = "fc67dfccb5fc90d7855ae903361eabd76f1e40a22a72ad3ef2d6ad27b5a60ce5";

const std::string CN_TURTLE_LITE_SLOW_HASH_V0 = "5e1891a15d5d85c09baf4a3bbe33675cfa3f77229c8ad66c01779e590528d6d3";
const std::string CN_TURTLE_LITE_SLOW_HASH_V1 = "ae7f864a7a2f2b07dcef253581e60a014972b9655a152341cb989164761c180a";
const std::string CN_TURTLE_LITE_SLOW_HASH_V2 = "b2172ec9466e1aee70ec8572a14c233ee354582bcb93f869d429744de5726a26";


const std::string CN_SOFT_SHELL_V0[] = {
  "c52cf980210591915ee217aaba57fa16661f1add0d09efebf7f393ee9867954b",
	"52b10fbebc1f9ae6bf9272b79696116472b67d74231a497227e9bd7b08e0065b",
	"4308207274251fa0125be5bae04226a611a8b24fe0d0fbaae3c9e7b4ffe9839c",
	"a18a8e1dff89f8183b74dcfe8b3c89c620dd5f45622e26229b28c3adffac22b2",
	"9f86b5da3306e3a9ae4bb2d1e4d7cc9759443a1ff56825282ae9a16d802ce570",
	"ba8f63de06a89d1377a0cdbd2e45aa9a4f43471f9e57c112d28061efa2b7017b",
	"d47333ab46a8e4e0090ee1c40deb31166cc7f0b79bb92f15d8695319c72a3431",
	"987de0d3bf7e8a338ee5fc27cd77dfcb0daf59a014bf40422a58cf6a2c61b33b",
	"f542eb7b192e01b1ba4a6312dd0252375884db62d4d6fefdf24d750b442709f0",
	"8871c627d487d6078c95cff978d03db2b042057077a9dd7175591f1b019893e4",
	"b8de11e551c47b0b804dc0d8379fc47c08a6831c4cdd75f9c0f32f9a82ede263",
	"fa376edee5cfffd95747a5ca0035c0e882bb2acd43286bda1ba3f1a541203d81",
	"41f135c50ba23da1ee7605e9724805af511b7045e137d2e3740963e3899f6c70",
	"57cf1dc5851c55d593e8867be1a9a6f68851e57632218d1e65d0f7fa9f8e9477",
	"5fe61f3256c6f8a1a2d1eb82001d9a534dbddd7a175fba78c2e8ad55e0e86e05",
	"8ddc72544121e80696ab09d19e4b4cf3e2c04c30e0f3aa4520922e1d801c4666",
	"523043ab2619f5c11a1398ade391223a8ac4af52c2b83a8e7761557bd9411f7c",
	"9ff11634ea54555c811282f24f3cea1ff50565d66a0fca45173b230084383052",
	"3fd14303e2cfe2166d15ffc11f44ec867edcaa8e7d98ba71be56269b1f813c29",
	"6ee72aa7fd46a95150f0224853caaa5169ece51eff7a0add182dd2c39df40f91",
	"471f771573819c271d2fa3b6705ac56ece7e3d6093f0b444e2504c2dd6e765bc",
	"10fb433f96f8d78cf9b893854e07ad0ed49476653be28e4534b0a85088977e49",
	"c4349f9556ea10201153649d3ab06bbc3083a5cbc6e24e588079854ab6df6006",
	"99b1b33bd412f62af7977f7c6e1a6c9e787c55adddc47f7d32f0260a50c65169",
	"e4404d56864180c990753d7503d1130fab972107698750a65ee4ed8d39c945f0",
	"dca2d232715f51be9146b8860dccb997d021f2acca9ba729bfe8a479db9fc63e",
	"551eccb82705eca5fc06b1d779f5d43c1b207f4ccb6a40eb78257a9275c71701",
	"97c90ce99f0ce29be736a741d9c0f849b2a57636f97ca8abac431f7466279ad1",
	"d463c7db90c09a293704ce0571c2921e7961f818d108e8f918eabbeaf2f156e0",
	"cc688b400b458c5f60227f4c6d1f91e3966594d2784ee59b70e10fe5aca731fa",
	"17ce1dcf2dc357370ce1b9eea749dad82498907bfcaa96fd90ce390e962cf722",
	"a576a6c77777538174b73f7e9004bcb29e5a516d65bf818a016b2481e61b9869",
	"5e1891a15d5d85c09baf4a3bbe33675cfa3f77229c8ad66c01779e590528d6d3",
	"a576a6c77777538174b73f7e9004bcb29e5a516d65bf818a016b2481e61b9869",
	"17ce1dcf2dc357370ce1b9eea749dad82498907bfcaa96fd90ce390e962cf722",
	"cc688b400b458c5f60227f4c6d1f91e3966594d2784ee59b70e10fe5aca731fa",
	"d463c7db90c09a293704ce0571c2921e7961f818d108e8f918eabbeaf2f156e0",
	"97c90ce99f0ce29be736a741d9c0f849b2a57636f97ca8abac431f7466279ad1",
	"551eccb82705eca5fc06b1d779f5d43c1b207f4ccb6a40eb78257a9275c71701",
	"dca2d232715f51be9146b8860dccb997d021f2acca9ba729bfe8a479db9fc63e",
	"e4404d56864180c990753d7503d1130fab972107698750a65ee4ed8d39c945f0",
	"99b1b33bd412f62af7977f7c6e1a6c9e787c55adddc47f7d32f0260a50c65169",
	"c4349f9556ea10201153649d3ab06bbc3083a5cbc6e24e588079854ab6df6006",
	"10fb433f96f8d78cf9b893854e07ad0ed49476653be28e4534b0a85088977e49",
	"471f771573819c271d2fa3b6705ac56ece7e3d6093f0b444e2504c2dd6e765bc",
	"6ee72aa7fd46a95150f0224853caaa5169ece51eff7a0add182dd2c39df40f91",
	"3fd14303e2cfe2166d15ffc11f44ec867edcaa8e7d98ba71be56269b1f813c29",
	"9ff11634ea54555c811282f24f3cea1ff50565d66a0fca45173b230084383052",
	"523043ab2619f5c11a1398ade391223a8ac4af52c2b83a8e7761557bd9411f7c",
	"8ddc72544121e80696ab09d19e4b4cf3e2c04c30e0f3aa4520922e1d801c4666",
	"5fe61f3256c6f8a1a2d1eb82001d9a534dbddd7a175fba78c2e8ad55e0e86e05",
	"57cf1dc5851c55d593e8867be1a9a6f68851e57632218d1e65d0f7fa9f8e9477",
	"41f135c50ba23da1ee7605e9724805af511b7045e137d2e3740963e3899f6c70",
	"fa376edee5cfffd95747a5ca0035c0e882bb2acd43286bda1ba3f1a541203d81",
	"b8de11e551c47b0b804dc0d8379fc47c08a6831c4cdd75f9c0f32f9a82ede263",
	"8871c627d487d6078c95cff978d03db2b042057077a9dd7175591f1b019893e4",
	"f542eb7b192e01b1ba4a6312dd0252375884db62d4d6fefdf24d750b442709f0",
	"987de0d3bf7e8a338ee5fc27cd77dfcb0daf59a014bf40422a58cf6a2c61b33b",
	"d47333ab46a8e4e0090ee1c40deb31166cc7f0b79bb92f15d8695319c72a3431",
	"ba8f63de06a89d1377a0cdbd2e45aa9a4f43471f9e57c112d28061efa2b7017b",
	"9f86b5da3306e3a9ae4bb2d1e4d7cc9759443a1ff56825282ae9a16d802ce570",
	"a18a8e1dff89f8183b74dcfe8b3c89c620dd5f45622e26229b28c3adffac22b2",
	"4308207274251fa0125be5bae04226a611a8b24fe0d0fbaae3c9e7b4ffe9839c",
	"52b10fbebc1f9ae6bf9272b79696116472b67d74231a497227e9bd7b08e0065b",
	"c52cf980210591915ee217aaba57fa16661f1add0d09efebf7f393ee9867954b"
};

const std::string CN_SOFT_SHELL_V1[] = {
 "07136662062c56a0bd291de0f6fccaacd1d65c04aafb706858472ba41c350635",
	"96d05072588b6af73f80f82965600884af14722c4a6d97d1c8401c25fb463b72",
	"98d12dbadfed8df2730dca0f4df4999e669e23e09cc8e0d26aed1a8ea58a7ef6",
	"01c984c764dd212c7dcb5f721cd8b0a9ba74922464c0be72a18f831d79a82051",
	"825b2ab5cf7a27c9224721bd534935a0b59e751f446c0ceef7c3e8ebbd83df0f",
	"30bb6a2a8855c44cd4213270814ac1d6f23fb35151cedd5f6a4f18c6b2fc862d",
	"17fbd518449e477abe3fd8c58015ee753bf97417b53c89ed5345c9cd87dabc4b",
	"21f71a468bd09e0d076494ded7a92948a68fc8679be0555e2605604338f91b7e",
	"26f37dc3ff4e67e2a8925a5ffe1b6ce8288e657cf7306a94e17ec267cedaf94f",
	"258876e39df5b05e93b76630a9d32596bd593da8283114567750aec2a92705b4",
	"0cdb9fb2a53217664738c9b67a207e98101641b123be770c96cfa68181726db7",
	"458dc28dd08249c0d062654eb35ddeeda740aed36b00f8101cd4bfd7527adae3",
	"e9b903555e8ab6791201b9ce91fc8faa5ca3e375899be2d230441187b704293e",
	"a564a251f5b437cb229e2bceaf316e9583cf4d91024c479ab7c8260a13539289",
	"5d07b29bb135a998dd1fdd2f4746535d79f49a2e879154b3d0b25fda9f8923cb",
	"3c571bb0a7646d2d8dcd720ca0e694397115705a5e7fc66f5a698ca25ff8fc88",
	"9167eb4a53da1436e7d926a75cb35413e8de835e3d7c963fce216fe8031a97e3",
	"3ff5807c15911d04d9cfd71f3a481bb0ee99b2e4d9eb94572c82f0501a785fa8",
	"1648322b9cc0de51e8e24ad1edec63c58910bc2189a25214c31b976c581e784d",
	"09ec5c56df52d6760b2a51f5a294cf74583930c515143ae4daed235fed3010fd",
	"e0682412fb75344db1c8e3452acf488b1fd85f0ba9cd19aa8f5968b0301b19b4",
	"f0a2bf64c9ab9ed8632712f92a695e69602d240c0650eb416faeb255bddf2692",
	"ae49735e9ca537ab7210a24e1f16123fb3814546167000fc89f3171f8ab4e9e6",
	"3fcc9f385b794cbeba5d717099a790aa33d6f4754ce05009557b72db3a6bea4a",
	"5f970c541654b8eb3c9e8e2bb1d0dc67ba7177fb0392adccd230e646a6da75a9",
	"6ee774ead0d3fd50cb8bfbd7d58a9d08ce1758b9119078500fcb07f018425bb9",
	"61330f561004d5b3075088e9f2d162509a2c69d3b5ea1597ff1f5cc91988262a",
	"138ba08f6fd97fd574fbe870aa19a893d7735f6075acb47bb51172a034a4133b",
	"00461445f6e63e8a8f5e72f9aa8552ec489a7e49c93f6937adb0b1e702454abb",
	"7bf53be2fa1f78ce424dfa72643aa8927521317a7c4bfb626346952b87b7c516",
	"58d3d0edd3576ab089b800373b003a74432a310162d30a904c63dbbeff3427de",
	"823b2bdd129b3335ecedeb63522e1974a9ac1c13d705059291afe2354d98e1ac",
	"ae7f864a7a2f2b07dcef253581e60a014972b9655a152341cb989164761c180a",
	"823b2bdd129b3335ecedeb63522e1974a9ac1c13d705059291afe2354d98e1ac",
	"58d3d0edd3576ab089b800373b003a74432a310162d30a904c63dbbeff3427de",
	"7bf53be2fa1f78ce424dfa72643aa8927521317a7c4bfb626346952b87b7c516",
	"00461445f6e63e8a8f5e72f9aa8552ec489a7e49c93f6937adb0b1e702454abb",
	"138ba08f6fd97fd574fbe870aa19a893d7735f6075acb47bb51172a034a4133b",
	"61330f561004d5b3075088e9f2d162509a2c69d3b5ea1597ff1f5cc91988262a",
	"6ee774ead0d3fd50cb8bfbd7d58a9d08ce1758b9119078500fcb07f018425bb9",
	"5f970c541654b8eb3c9e8e2bb1d0dc67ba7177fb0392adccd230e646a6da75a9",
	"3fcc9f385b794cbeba5d717099a790aa33d6f4754ce05009557b72db3a6bea4a",
	"ae49735e9ca537ab7210a24e1f16123fb3814546167000fc89f3171f8ab4e9e6",
	"f0a2bf64c9ab9ed8632712f92a695e69602d240c0650eb416faeb255bddf2692",
	"e0682412fb75344db1c8e3452acf488b1fd85f0ba9cd19aa8f5968b0301b19b4",
	"09ec5c56df52d6760b2a51f5a294cf74583930c515143ae4daed235fed3010fd",
	"1648322b9cc0de51e8e24ad1edec63c58910bc2189a25214c31b976c581e784d",
	"3ff5807c15911d04d9cfd71f3a481bb0ee99b2e4d9eb94572c82f0501a785fa8",
	"9167eb4a53da1436e7d926a75cb35413e8de835e3d7c963fce216fe8031a97e3",
	"3c571bb0a7646d2d8dcd720ca0e694397115705a5e7fc66f5a698ca25ff8fc88",
	"5d07b29bb135a998dd1fdd2f4746535d79f49a2e879154b3d0b25fda9f8923cb",
	"a564a251f5b437cb229e2bceaf316e9583cf4d91024c479ab7c8260a13539289",
	"e9b903555e8ab6791201b9ce91fc8faa5ca3e375899be2d230441187b704293e",
	"458dc28dd08249c0d062654eb35ddeeda740aed36b00f8101cd4bfd7527adae3",
	"0cdb9fb2a53217664738c9b67a207e98101641b123be770c96cfa68181726db7",
	"258876e39df5b05e93b76630a9d32596bd593da8283114567750aec2a92705b4",
	"26f37dc3ff4e67e2a8925a5ffe1b6ce8288e657cf7306a94e17ec267cedaf94f",
	"21f71a468bd09e0d076494ded7a92948a68fc8679be0555e2605604338f91b7e",
	"17fbd518449e477abe3fd8c58015ee753bf97417b53c89ed5345c9cd87dabc4b",
	"30bb6a2a8855c44cd4213270814ac1d6f23fb35151cedd5f6a4f18c6b2fc862d",
	"825b2ab5cf7a27c9224721bd534935a0b59e751f446c0ceef7c3e8ebbd83df0f",
	"01c984c764dd212c7dcb5f721cd8b0a9ba74922464c0be72a18f831d79a82051",
	"98d12dbadfed8df2730dca0f4df4999e669e23e09cc8e0d26aed1a8ea58a7ef6",
	"96d05072588b6af73f80f82965600884af14722c4a6d97d1c8401c25fb463b72",
	"07136662062c56a0bd291de0f6fccaacd1d65c04aafb706858472ba41c350635"
};

const std::string CN_SOFT_SHELL_V2[] = {
  "28697d8283af6911555170f77de32238ff7018a82a5273730afa4fa2725e30fe",
	"06f90fb5cf562bf1ab560e8c19664e7aad07ad3b6927439aa1641df4fd009f24",
	"b6607cbf0df65da4689b4f2c219d5d319c4ea28b93ac89a6770666126f210c09",
	"4726a5a37bc62d1c5620d13842146fdadfaf43f65cb25b4f6f3f09324f98c4ec",
	"34a71ce652522891266323a7f15219d1c91166d7a3ef51f841275eb8f54da2ce",
	"455c6ea9779b841e02cf4421928f69a450007f15611fdb8893003d954b43b3f5",
	"4402b3fb1de5eea39162c9f4e612476274dd899775f65e500795e793c0d8cd99",
	"f2f662b8b4fa79c7cea7b724b7db3ff8d171a0941ce0c2fb0b464c41eb15fae7",
	"6a3f473cc92ad1f5dc70431fc2c7f41e83bd06136ac212fe6862eced7390a139",
	"774bc287a1140a3fc8684fa8fe55e33fcc1f2068b63a46a0869dc6c36707dd79",
	"9cb273312097ba425cd946ab32cf34d47fcd4cb7e5e05b9cddc4c466f92c2349",
	"add94a3c074254a72c3260b4ccc9fc465df814de4ad81f819b0509f9da66cbe2",
	"94af06415bcdfdbb9c58f8263542b31969c16787c01d93f0e00c7a8c607a5831",
	"43a93c7ccabfe8832699df444930dd7923158ca8b6c27f310023fdf49a1827d2",
	"dd5ae99e0480d876ac93747a0ce1540c9ced75d33017e6d243575b35dc7651c9",
	"a86e460f2145b088c0122041d5370819468eed92b013f0eb7753629a3e66b69a",
	"6fe009be068e42f7f6044a8d49f829a265cc8cc15fc4e1df7c0ba35ec086c686",
	"9990a36c89cb89a25a6921ab2d5580a348e19013a025cb0a69343312f8fa9385",
	"955575813c22e8ac7c8d16d6c178d0630af0cd4f83abcfff09087e73290e7c7c",
	"f174dddebbe0852eb151d7834e512588a95d6ae0e364ad067ef4900adb19b569",
	"2e627fd3739ab7c7bd0dbb03d6bc304be58f1c3e6f14ce71be772ddaeac74a0c",
	"b1aa8e8d5a14aaedb37bb5088197438e74c9d133e5f11bfa9a3a880539a9e931",
	"7e809c2713fce2c54f79669614870353e32a1df0d0ecf3bbdf845acce913f22a",
	"d6d01afb954e8ea0206cee6029db46463d0901ab9e34ff670f2a0ccd912143f8",
	"485ae4af8b58978ce9224d67d8d0dab217ffc451cd19c5902419704224aeede4",
	"a3957479d032bc4601f35f94577e39cf66ab022bb30ceb50f4b8a50abe3d8db6",
	"6ef63e665ccbce5d223f6a3dc4ea146aaa05c5d8ef199cc4135e1862d043a5fd",
	"c7df7b1c77931422ba9ec3bf05733b418264e9626b2d9ef89445c300556aba22",
	"725ac7a556f9f11bfadf5145b2b583802585cef914e239c3df34b6d4b86af3a3",
	"1a477755459883debbde53a8a11ae5125f85150839925a2863e756d64aed843f",
	"eccfa295ba92de519186497005c1d54f1f83d444fcfe1e301f64709049c36e54",
	"4f92048afa28c838721dd6d8bdf75a9181822797e77e9790a5748fb0fb497f25",
	"b2172ec9466e1aee70ec8572a14c233ee354582bcb93f869d429744de5726a26",
	"4f92048afa28c838721dd6d8bdf75a9181822797e77e9790a5748fb0fb497f25",
	"eccfa295ba92de519186497005c1d54f1f83d444fcfe1e301f64709049c36e54",
	"1a477755459883debbde53a8a11ae5125f85150839925a2863e756d64aed843f",
	"725ac7a556f9f11bfadf5145b2b583802585cef914e239c3df34b6d4b86af3a3",
	"c7df7b1c77931422ba9ec3bf05733b418264e9626b2d9ef89445c300556aba22",
	"6ef63e665ccbce5d223f6a3dc4ea146aaa05c5d8ef199cc4135e1862d043a5fd",
	"a3957479d032bc4601f35f94577e39cf66ab022bb30ceb50f4b8a50abe3d8db6",
	"485ae4af8b58978ce9224d67d8d0dab217ffc451cd19c5902419704224aeede4",
	"d6d01afb954e8ea0206cee6029db46463d0901ab9e34ff670f2a0ccd912143f8",
	"7e809c2713fce2c54f79669614870353e32a1df0d0ecf3bbdf845acce913f22a",
	"b1aa8e8d5a14aaedb37bb5088197438e74c9d133e5f11bfa9a3a880539a9e931",
	"2e627fd3739ab7c7bd0dbb03d6bc304be58f1c3e6f14ce71be772ddaeac74a0c",
	"f174dddebbe0852eb151d7834e512588a95d6ae0e364ad067ef4900adb19b569",
	"955575813c22e8ac7c8d16d6c178d0630af0cd4f83abcfff09087e73290e7c7c",
	"9990a36c89cb89a25a6921ab2d5580a348e19013a025cb0a69343312f8fa9385",
	"6fe009be068e42f7f6044a8d49f829a265cc8cc15fc4e1df7c0ba35ec086c686",
	"a86e460f2145b088c0122041d5370819468eed92b013f0eb7753629a3e66b69a",
	"dd5ae99e0480d876ac93747a0ce1540c9ced75d33017e6d243575b35dc7651c9",
	"43a93c7ccabfe8832699df444930dd7923158ca8b6c27f310023fdf49a1827d2",
	"94af06415bcdfdbb9c58f8263542b31969c16787c01d93f0e00c7a8c607a5831",
	"add94a3c074254a72c3260b4ccc9fc465df814de4ad81f819b0509f9da66cbe2",
	"9cb273312097ba425cd946ab32cf34d47fcd4cb7e5e05b9cddc4c466f92c2349",
	"774bc287a1140a3fc8684fa8fe55e33fcc1f2068b63a46a0869dc6c36707dd79",
	"6a3f473cc92ad1f5dc70431fc2c7f41e83bd06136ac212fe6862eced7390a139",
	"f2f662b8b4fa79c7cea7b724b7db3ff8d171a0941ce0c2fb0b464c41eb15fae7",
	"4402b3fb1de5eea39162c9f4e612476274dd899775f65e500795e793c0d8cd99",
	"455c6ea9779b841e02cf4421928f69a450007f15611fdb8893003d954b43b3f5",
	"34a71ce652522891266323a7f15219d1c91166d7a3ef51f841275eb8f54da2ce",
	"4726a5a37bc62d1c5620d13842146fdadfaf43f65cb25b4f6f3f09324f98c4ec",
	"b6607cbf0df65da4689b4f2c219d5d319c4ea28b93ac89a6770666126f210c09",
	"06f90fb5cf562bf1ab560e8c19664e7aad07ad3b6927439aa1641df4fd009f24",
	"28697d8283af6911555170f77de32238ff7018a82a5273730afa4fa2725e30fe"
};

static inline bool CompareHashes(const Hash leftHash, const std::string right)
{
  Hash rightHash = Hash();
  if (!Common::podFromHex(right, rightHash)) {
    return false;
  }

  return (leftHash == rightHash);
}

/* Check if we're testing a v1 or v2 hash function */
/* Hacky as fuck lmao */
bool need43BytesOfData(std::string hashFunctionName)
{
    return (hashFunctionName.find("v1") != std::string::npos 
        || hashFunctionName.find("v2") != std::string::npos);
}

/* Bit of hackery so we can get the variable name of the passed in function.
   This way we can print the test we are currently performing. */
#define TEST_HASH_FUNCTION(hashFunction, expectedOutput) \
   testHashFunction(hashFunction, expectedOutput, #hashFunction, -1)

#define TEST_HASH_FUNCTION_WITH_HEIGHT(hashFunction, expectedOutput, height) \
    testHashFunction(hashFunction, expectedOutput, #hashFunction, height, height)

template<typename T, typename ...Args>
void testHashFunction(
    T hashFunction,
    std::string expectedOutput,
    std::string hashFunctionName,
    int64_t height,
    Args && ... args)
{
    const BinaryArray& rawData = Common::fromHex(INPUT_DATA);

    if (need43BytesOfData(hashFunctionName) && rawData.size() < 43)
    {
        return;
    }

    Hash hash = Hash();

    /* Perform the hash, with a height if given */
    hashFunction(rawData.data(), rawData.size(), hash, std::forward<Args>(args)...);

    if (height == -1)
    {
        std::cout << hashFunctionName << ": " << hash << std::endl;
    }
    else
    {
        std::cout << hashFunctionName << " (" << height << "): " << hash << std::endl;
    }

    /* Verify the hash is as expected */
    assert(CompareHashes(hash, expectedOutput));
}

/* Bit of hackery so we can get the variable name of the passed in function.
   This way we can print the test we are currently performing. */
#define BENCHMARK(hashFunction, iterations) \
   benchmark(hashFunction, #hashFunction, iterations)

template<typename T>
void benchmark(T hashFunction, std::string hashFunctionName, uint64_t iterations)
{
    const BinaryArray& rawData = Common::fromHex(INPUT_DATA);

    if (need43BytesOfData(hashFunctionName) && rawData.size() < 43)
    {
        return;
    }

    Hash hash = Hash();

    auto startTimer = std::chrono::high_resolution_clock::now();

    for (uint64_t i = 0; i < iterations; i++)
    {
        hashFunction(rawData.data(), rawData.size(), hash);
    }

    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTimer;

    std::cout << hashFunctionName << ": "
              << (iterations / std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count())
              << " H/s\n";
}

void benchmarkUnderivePublicKey()
{
    Crypto::KeyDerivation derivation;

    Crypto::PublicKey txPublicKey;
    Common::podFromHex("f235acd76ee38ec4f7d95123436200f9ed74f9eb291b1454fbc30742481be1ab", txPublicKey);

    Crypto::SecretKey privateViewKey;
    Common::podFromHex("89df8c4d34af41a51cfae0267e8254cadd2298f9256439fa1cfa7e25ee606606", privateViewKey);

    Crypto::generate_key_derivation(txPublicKey, privateViewKey, derivation);

    const uint64_t loopIterations = 600000;

    auto startTimer = std::chrono::high_resolution_clock::now();

    Crypto::PublicKey spendKey;

    Crypto::PublicKey outputKey;
    Common::podFromHex("4a078e76cd41a3d3b534b83dc6f2ea2de500b653ca82273b7bfad8045d85a400", outputKey);

    for (uint64_t i = 0; i < loopIterations; i++)
    {
        /* Use i as output index to prevent optimization */
        Crypto::underive_public_key(derivation, i, outputKey, spendKey);
    }

    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTimer;

    /* Need to use microseconds here then divide by 1000 - otherwise we'll just get '0' */
    const auto timePerDerivation = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count() / loopIterations;

    std::cout << "Time to perform underivePublicKey: " << timePerDerivation / 1000.0 << " ms" << std::endl;
}

void benchmarkGenerateKeyDerivation()
{
    Crypto::KeyDerivation derivation;

    Crypto::PublicKey txPublicKey;
    Common::podFromHex("f235acd76ee38ec4f7d95123436200f9ed74f9eb291b1454fbc30742481be1ab", txPublicKey);

    Crypto::SecretKey privateViewKey;
    Common::podFromHex("89df8c4d34af41a51cfae0267e8254cadd2298f9256439fa1cfa7e25ee606606", privateViewKey);

    const uint64_t loopIterations = 60000;

    auto startTimer = std::chrono::high_resolution_clock::now();

    for (uint64_t i = 0; i < loopIterations; i++)
    {
        Crypto::generate_key_derivation(txPublicKey, privateViewKey, derivation);
    }

    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTimer;

    const auto timePerDerivation = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count() / loopIterations;

    std::cout << "Time to perform generateKeyDerivation: " << timePerDerivation / 1000.0 << " ms" << std::endl;
}

int main(int argc, char** argv)
{
    bool o_help, o_version, o_benchmark;
    int o_iterations;

    cxxopts::Options options(argv[0], getProjectCLIHeader());

    options.add_options("Core")
        ("h,help", "Display this help message", cxxopts::value<bool>(o_help)->implicit_value("true"))
        ("v,version", "Output software version information", cxxopts::value<bool>(o_version)->default_value("false")->implicit_value("true"));

    options.add_options("Performance Testing")
        ("b,benchmark", "Run quick performance benchmark", cxxopts::value<bool>(o_benchmark)->default_value("false")->implicit_value("true"))
        ("i,iterations", "The number of iterations for the benchmark test. Minimum of 1,000 iterations required.",
            cxxopts::value<int>(o_iterations)->default_value(std::to_string(PERFORMANCE_ITERATIONS)), "#");

    try
    {
        auto result = options.parse(argc, argv);
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << "Error: Unable to parse command line argument options: " << e.what() << std::endl << std::endl;
        std::cout << options.help({}) << std::endl;
        exit(1);
    }

    if (o_help) // Do we want to display the help message?
    {
        std::cout << options.help({}) << std::endl;
        exit(0);
    }
    else if (o_version) // Do we want to display the software version?
    {
        std::cout << getProjectCLIHeader() << std::endl;
        exit(0);
    }

    if (o_iterations < 1000 && o_benchmark)
    {
        std::cout << std::endl << "Error: The number of --iterations should be at least 1,000 for reasonable accuracy" << std::endl;
        exit(1);
    }

    int o_iterations_long = o_iterations * PERFORMANCE_ITERATIONS_LONG_MULTIPLIER;

    try
    {
        std::cout << getProjectCLIHeader() << std::endl;

        std::cout << "Input: " << INPUT_DATA << std::endl << std::endl;

        TEST_HASH_FUNCTION(cn_slow_hash_v0, CN_SLOW_HASH_V0);
        TEST_HASH_FUNCTION(cn_slow_hash_v1, CN_SLOW_HASH_V1);
        TEST_HASH_FUNCTION(cn_slow_hash_v2, CN_SLOW_HASH_V2);
        
        std::cout << std::endl;

        TEST_HASH_FUNCTION(cn_lite_slow_hash_v0, CN_LITE_SLOW_HASH_V0);
        TEST_HASH_FUNCTION(cn_lite_slow_hash_v1, CN_LITE_SLOW_HASH_V1);
        TEST_HASH_FUNCTION(cn_lite_slow_hash_v2, CN_LITE_SLOW_HASH_V2);

        std::cout << std::endl;

        TEST_HASH_FUNCTION(cn_dark_slow_hash_v0, CN_DARK_SLOW_HASH_V0);
        TEST_HASH_FUNCTION(cn_dark_slow_hash_v1, CN_DARK_SLOW_HASH_V1);
        TEST_HASH_FUNCTION(cn_dark_slow_hash_v2, CN_DARK_SLOW_HASH_V2);

        std::cout << std::endl;

        TEST_HASH_FUNCTION(cn_dark_lite_slow_hash_v0, CN_DARK_LITE_SLOW_HASH_V0);
        TEST_HASH_FUNCTION(cn_dark_lite_slow_hash_v1, CN_DARK_LITE_SLOW_HASH_V1);
        TEST_HASH_FUNCTION(cn_dark_lite_slow_hash_v2, CN_DARK_LITE_SLOW_HASH_V2);
        
        std::cout << std::endl;

        TEST_HASH_FUNCTION(cn_turtle_slow_hash_v0, CN_TURTLE_SLOW_HASH_V0);
        TEST_HASH_FUNCTION(cn_turtle_slow_hash_v1, CN_TURTLE_SLOW_HASH_V1);
        TEST_HASH_FUNCTION(cn_turtle_slow_hash_v2, CN_TURTLE_SLOW_HASH_V2);

        std::cout << std::endl;

        TEST_HASH_FUNCTION(cn_turtle_lite_slow_hash_v0, CN_TURTLE_LITE_SLOW_HASH_V0);
        TEST_HASH_FUNCTION(cn_turtle_lite_slow_hash_v1, CN_TURTLE_LITE_SLOW_HASH_V1);
        TEST_HASH_FUNCTION(cn_turtle_lite_slow_hash_v2, CN_TURTLE_LITE_SLOW_HASH_V2);

        std::cout << std::endl;

        for (uint64_t height = 0; height <= 8192; height += 512)
        {
            TEST_HASH_FUNCTION_WITH_HEIGHT(cn_soft_shell_slow_hash_v0, CN_SOFT_SHELL_V0[height / 512], height);
        }

        std::cout << std::endl;

        for (uint64_t height = 0; height <= 8192; height += 512)
        {
            TEST_HASH_FUNCTION_WITH_HEIGHT(cn_soft_shell_slow_hash_v1, CN_SOFT_SHELL_V1[height / 512], height);
        }

        std::cout << std::endl;

        for (uint64_t height = 0; height <= 8192; height += 512)
        {
            TEST_HASH_FUNCTION_WITH_HEIGHT(cn_soft_shell_slow_hash_v2, CN_SOFT_SHELL_V2[height / 512], height);
        }

        if (o_benchmark)
        {
            std::cout <<  "\nPerformance Tests: Please wait, this may take a while depending on your system...\n\n";

            benchmarkUnderivePublicKey();
            benchmarkGenerateKeyDerivation();

            BENCHMARK(cn_slow_hash_v0, o_iterations);
            BENCHMARK(cn_slow_hash_v1, o_iterations);
            BENCHMARK(cn_slow_hash_v2, o_iterations);

            BENCHMARK(cn_lite_slow_hash_v0, o_iterations);
            BENCHMARK(cn_lite_slow_hash_v1, o_iterations);
            BENCHMARK(cn_lite_slow_hash_v2, o_iterations);

            BENCHMARK(cn_dark_slow_hash_v0, o_iterations);
            BENCHMARK(cn_dark_slow_hash_v1, o_iterations);
            BENCHMARK(cn_dark_slow_hash_v2, o_iterations);

            BENCHMARK(cn_dark_lite_slow_hash_v0, o_iterations);
            BENCHMARK(cn_dark_lite_slow_hash_v1, o_iterations);
            BENCHMARK(cn_dark_lite_slow_hash_v2, o_iterations);

            BENCHMARK(cn_turtle_slow_hash_v0, o_iterations_long);
            BENCHMARK(cn_turtle_slow_hash_v1, o_iterations_long);
            BENCHMARK(cn_turtle_slow_hash_v2, o_iterations_long);

            BENCHMARK(cn_turtle_lite_slow_hash_v0, o_iterations_long);
            BENCHMARK(cn_turtle_lite_slow_hash_v1, o_iterations_long);
            BENCHMARK(cn_turtle_lite_slow_hash_v2, o_iterations_long);
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Something went terribly wrong...\n" << e.what() << "\n\n";
    }
}
