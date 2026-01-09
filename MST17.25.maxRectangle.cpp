// Created: 2026-01-09
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一份单词的清单，设计一个算法，创建由字母组成的面积最大的矩形，
其中每一行组成一个单词(自左向右)，每一列也组成一个单词(自上而下)。
不要求这些单词在清单里连续出现，但要求所有行等长，所有列等高。
如果有多个面积最大的矩形，输出任意一个均可。一个单词可以重复使用。
示例 1：
输入：{"this", "real", "hard", "trh", "hea", "iar", "sld"}
输出：
	{
	  "this",
	  "real",
	  "hard"
	}
示例 2：
输入：{"aa"}
输出：{"aa","aa"}
说明：
	words.length <= 1000
	words{i}.length <= 100
	数据保证单词足够随机 */

class Solution1 {
public:
	vector<string> maxRectangle(vector<string> &wordsIn) {
		resId.clear();
		area = 0;
		words = std::move(wordsIn);
		unordered_map<unsigned, vector<int>> size2id;
		int n = words.size();
		for(int i = 0; i < n; ++i) {
			size2id[words[i].size()].push_back(i);
		}
		TrieTree *root = new TrieTree();
		for(int i = 0; i < n; ++i) {
			TrieTree *p = root;
			int nw = words[i].size();
			for(int j = 0; j < nw; ++j) {
				int index = words[i][j] - 'a';
				TrieTree *&chird = p->children[index];
				if(!chird) {
					chird = new TrieTree();
				}
				p = chird;
			}
			p->endid = i; // 有相同元素也无所谓
		}
		for(auto &[size, lines] : size2id) {
			vector<int> curr;
			dfs(size, lines, curr, vector<TrieTree *>(size, root));
		}
		vector<string> res;
		for(auto id : resId) {
			res.emplace_back(words[id]);
		}
		return res;
	}

private:
	int area;
	vector<int> resId;
	vector<string> words;
	struct TrieTree {
		int endid = -1;
		array<TrieTree *, 26> children {};
	};
	void dfs(int size, vector<int> &lines, vector<int> &curr, vector<TrieTree *> root) {
		if(!curr.empty()) {
			bool canUse = true;
			for(auto r : root) {
				if(r->endid == -1) {
					canUse = false;
				}
			}
			if(canUse) {
				int currArea = curr.size() * words[curr[0]].size();
				if(currArea > area) {
					resId = curr;
					area = currArea;
				}
			}
		}
		for(int lid : lines) {
			string &str = words[lid];
			vector<TrieTree *> rootnext;
			rootnext.reserve(size);
			for(int i = 0; i < size; ++i) {
				if(!root[i]->children[str[i] - 'a']) {
					break;
				} else {
					rootnext.push_back(root[i]->children[str[i] - 'a']);
				}
			}
			if(rootnext.size() != size) continue;
			curr.push_back(lid);
			dfs(size, lines, curr, rootnext);
			curr.pop_back();
		}
	}
}; // 先用全部word构建Trie树，并将相同长度的word放到一起作为一系列可选的行分组，在每一个行分组上每次选择下一个行，并且移动每一列的TireTree节点的位置
// 会超时，主要有两个优化点：1、在Trie的路径上记录最大长度，如果当前的最大长度*宽度小于已保存的最大值，则没有必要往下继续
//                         2、将指针型TireTire修改为vector型

class Solution {
public:
	vector<string> maxRectangle(vector<string> &wordsIn) {
		resId.clear();
		area = 0;
		words = std::move(wordsIn);
		nodes = vector<TrieTree>(1);
		unordered_map<unsigned, vector<int>> size2id;
		int n = words.size(), allLen = 0;
		for(int i = 0; i < n; ++i) {
			allLen += words[i].size();
			size2id[words[i].size()].push_back(i);
		}
		nodes.reserve(allLen);
		for(int i = 0; i < n; ++i) {
			int nw = words[i].size(), nodeid = 0;
			for(int j = 0; j < nw; ++j) {
				nodes[nodeid].maxDepth = max(nodes[nodeid].maxDepth, nw);
				int index = words[i][j] - 'a';
				if(nodes[nodeid].children[index] == -1) {
					nodes[nodeid].children[index] = (int)nodes.size();
					nodes.emplace_back();
				}
				nodeid = nodes[nodeid].children[index];
			}
			nodes[nodeid].maxDepth = max(nodes[nodeid].maxDepth, nw);
			nodes[nodeid].endid = i; // 有相同元素也无所谓
		}
		for(auto &[size, lines] : size2id) {
			vector<int> curr, rootid(size, 0);
			dfs(size, lines, curr, rootid);
		}
		vector<string> res;
		for(auto id : resId) {
			res.emplace_back(words[id]);
		}
		return res;
	}

private:
	struct TrieTree {
		int endid = -1;
		int maxDepth = 0;
		array<int, 26> children;
		TrieTree() {
			children.fill(-1);
		}
	};
	int area;
	vector<int> resId;
	vector<string> words;
	vector<TrieTree> nodes;
	void dfs(int size, vector<int> &lines, vector<int> &curr, vector<int> &rootid) {
		if(!curr.empty()) {
			bool canUse = true;
			int maxDepth = INT_MAX;
			for(auto id : rootid) {
				if(nodes[id].endid == -1) {
					canUse = false;
				}
				maxDepth = min(maxDepth, nodes[id].maxDepth);
			}
			if(canUse) {
				int currArea = size * curr.size();
				if(currArea > area) {
					resId = curr;
					area = currArea;
				}
			}
			if(size * maxDepth <= area) {
				return;
			} // 不剪枝超时
		}
		vector<int> rootnext(size);
		for(int lid : lines) {
			bool find = true;
			auto &str = words[lid];
			for(int i = 0; i < size; ++i) {
				if(nodes[rootid[i]].children[str[i] - 'a'] == -1) {
					find = false;
					break;
				} else {
					rootnext[i] = nodes[rootid[i]].children[str[i] - 'a'];
				}
			}
			if(!find) continue;
			curr.push_back(lid);
			dfs(size, lines, curr, rootnext);
			curr.pop_back();
		}
	}
};

int main() {
	Solution sol;
	vector<string> words;
	words = { "cwsmqtaausjakauhujlpgjwpapsyunylpivxzbbdkxfxmeoypt",
		"n",
		"gd",
		"ib",
		"zj",
		"uw",
		"fg",
		"nr",
		"qp",
		"fb",
		"vq",
		"gz",
		"un",
		"tl",
		"gn",
		"bshvfxaadfogxjjgmjuwijdcpnluaztzyyzhwkkpsznvilhhcc",
		"bg",
		"zb",
		"qc",
		"rs",
		"jj",
		"khkxfuyqkfmrmqnxkbokatfkaplbdallpjdryysfrqbjuzatqf",
		"ju",
		"iq",
		"hx",
		"zkvygirllpckgxwctgiyzbcuffnqolmbghvzaejzpqckrmjzwu",
		"aj",
		"mn",
		"ad",
		"oa",
		"kr",
		"bs",
		"mh",
		"pe",
		"ce",
		"xn",
		"jc",
		"ha",
		"zk",
		"gf",
		"xw",
		"ku",
		"ll",
		"fn",
		"ii",
		"gw",
		"yu",
		"up",
		"xh",
		"lo",
		"bsjsjppqxtqwrsxeyamophripgayjuzupkbqmkqmeqjkilcubh",
		"ne",
		"z",
		"bv",
		"ja",
		"rv",
		"lh",
		"dq",
		"ve",
		"jk",
		"qu",
		"zw",
		"lw",
		"aw",
		"rm",
		"bb",
		"xi",
		"rq",
		"zt",
		"js",
		"xu",
		"kw",
		"ro",
		"sf",
		"by",
		"gb",
		"mu",
		"jz",
		"gi",
		"boquvjhgadilhsbxhjtlmmutmnuttxugmhafppojfgbxghabuy",
		"yp",
		"lg",
		"cu",
		"ct",
		"mw",
		"xk",
		"sl",
		"zf",
		"eh",
		"so",
		"sp",
		"kp",
		"qz",
		"ty",
		"dy",
		"dz",
		"jt",
		"ey",
		"yt",
		"ih",
		"iwdggfxtdgklqpxdsarqexjbgepkdbkmnvdzbmdudhpjbngdxp",
		"hf",
		"mx",
		"uouzqwjkwdzvqfdhzpfvzpeajfkvtxdkcrwhvbqbhlqshyaybh",
		"ef",
		"ir",
		"adktqiniltegtvohcunbbxwzpmypkgodihutzinwiufbegevqc",
		"bh",
		"dm",
		"fk",
		"uk",
		"ae",
		"nm",
		"qk",
		"toilgaddlgxypkpvfpkctfyiudjcbjpfedgjmvsfrenrvroxdi",
		"ao",
		"bthhjsqqrqjubfivllsydjmmwpjlymynhqpofwlayzxwksicuu",
		"tjecqwbnfgnpqaqkfkyailypqaubuqwcmhjimphfazbroagzyb",
		"xr",
		"gs",
		"r",
		"rn",
		"oiikbjjpjngxprbkkerocamygvghxwxboyxafyumexsyycsfcu",
		"sm",
		"ij",
		"fj",
		"ta",
		"fe",
		"ox",
		"rz",
		"cg",
		"vv",
		"cz",
		"pv",
		"uj",
		"em",
		"rl",
		"uv",
		"vy",
		"yzvaqlpeuafqfrgdxnsrtsizleobksnijtrvhcvjxzrvvwhlzj",
		"wl",
		"nu",
		"io",
		"bm",
		"lmkrzmfvhaidusnztyjdxchgthqabzerrnbysboyauwuiqgnrj",
		"pp",
		"whqplhrluofemarlwgvonyoivmkhaaugqfgifdpxyufaiikqaq",
		"cb",
		"ri",
		"ym",
		"lu",
		"pcgamtwwpqyokvdzimjmeompemhxewwjjmhywfinsjmmrrmnbi",
		"ncqfjjreumidraarkycprwzkdudpzkecyzkcyaxuuvhnfjfrtn",
		"to",
		"mr",
		"bycjuhplzcjrscepphwcccalrosgonyzgexlojtshileqceyyt",
		"sn",
		"xp",
		"kf",
		"ul",
		"pb",
		"iv",
		"ea",
		"ap",
		"su",
		"th",
		"kg",
		"ysukcysqdilqemxikiqynsifdeiblrvznedfrlalmzczqywmqv",
		"lj",
		"xz",
		"ra",
		"fo",
		"iy",
		"mm",
		"zu",
		"pwjpjxirlqswexleoeotuqudzpseowuqjihmbfmlepgquixppa",
		"ya",
		"dg",
		"lktvueuukxahguvplyocaoyqspfqvwgmrznztlaefxspicorpe",
		"dw",
		"nbznkghfiljhsvuiznshnzwkpuukikbzeyeuqrmthdrkncmjiv",
		"vr",
		"jh",
		"ly",
		"co",
		"bt",
		"bl",
		"wv",
		"er",
		"wd",
		"ye",
		"mi",
		"ny",
		"hy",
		"nz",
		"ip",
		"wk",
		"hn",
		"asaplbgmfnfaycpddojdcliwvuylsoiefsmkaazjzherdjbxus",
		"tr",
		"st",
		"sa",
		"ke",
		"ee",
		"wh",
		"px",
		"ws",
		"ng",
		"qflxhbcepgukmlsyeneiuvagdnpyallkepgniutddpkrhpsecr",
		"jl",
		"cy",
		"av",
		"pt",
		"hj",
		"rk",
		"kd",
		"gx",
		"kk",
		"esfpdztmjtnbglsslxvwkyrkrhwybbwhataverbwkqghupczvo",
		"qv",
		"vo",
		"xc",
		"gr",
		"ml",
		"uf",
		"hq",
		"hdhqghtxfhmrmdpmzdaylngtgoqznqaztchfanvumqdraxeixq",
		"ak",
		"bz",
		"yk",
		"rpuwhkpibuypilyabjnqnekaptlypkgxozbjvozptessyyvicr",
		"lb",
		"yx",
		"gqovsmbldqwfyroyyweeukudtxikqatyauguorjvgzrppjydtl",
		"da",
		"dn",
		"du",
		"atsbxpvmjtcernkghoznhgvslekssoigjnneooveoruaqgyytn",
		"qg",
		"li",
		"py",
		"tw",
		"dj",
		"if",
		"ns",
		"eq",
		"ni",
		"si",
		"tx",
		"as",
		"at",
		"sy",
		"jx",
		"in",
		"mp",
		"uzlwwhtvmfilekqrliftjgnqxnjrnsltcywobftyfsaxiazlqz",
		"xf",
		"zsnuzoiqeezwujyngvppjofnksppakejmlgrbknlpqhckeungv",
		"ux",
		"uu",
		"jhxynhixxbrrkufmtxdjikkevrvntsgngttgudondepizpnikd",
		"rf",
		"pj",
		"rc",
		"m",
		"nh",
		"zs",
		"am",
		"jd",
		"wg",
		"ms",
		"bw",
		"kx",
		"ka",
		"yn",
		"tg",
		"gj",
		"fi",
		"krstgziiqabggvvufvuszmsyiiaxdwzawrbozbrvafuefoglqs",
		"te",
		"aa",
		"jg",
		"nf",
		"yw",
		"yq",
		"zm",
		"nt",
		"en",
		"rucggdxdkynxyvkhvbyanotbtqbfzpzyavzbkahjgpfjllzyef",
		"d",
		"kj",
		"elhfspkxdxqnpmpkdcgmosmglcdcgvqwbrxfzmlaurtvaythjk",
		"kq",
		"vc",
		"ho",
		"wj",
		"xq",
		"ic",
		"ev",
		"wy",
		"tc",
		"fooqakmfhzcsotjjkozdbijsoetdwqiktlisrstduwlnmksslh",
		"uz",
		"el",
		"hw",
		"gp",
		"np",
		"ph",
		"be",
		"dd",
		"mo",
		"lc",
		"va",
		"tq",
		"vl",
		"ln",
		"az",
		"tz",
		"dkidytafkhhlbmdhzkgqmcvctbafroiitafzwoyoohkzhhikie",
		"v",
		"xx",
		"jf",
		"rfzndcdrshuillnjwrttsorsjqemazazpeifkoecqkvewbtbth",
		"us",
		"cj",
		"mv",
		"fl",
		"qj",
		"ck",
		"bk",
		"s",
		"ls",
		"wo",
		"htfmmbnstvtfixgolzkebgjxdtimcvnjiddkzokkuoebptxhuo",
		"rw",
		"mz",
		"vu",
		"it",
		"wn",
		"hz",
		"xmgsracbzttbwqpiwpflflhvmcjedvnrwxxptjbifdstrpipwv",
		"wm",
		"yb",
		"tu",
		"cd",
		"ds",
		"bu",
		"db",
		"gadtwqkazgwellbnmhirhcknahqxeiqgmdgumtujnkedlufyjs",
		"vlmqrilyscywjlytqzvogakjypnksnhhmovdgikqcbjtfescug",
		"t",
		"nc",
		"yr",
		"ch",
		"i",
		"rd",
		"eb",
		"pq",
		"xy",
		"do",
		"hu",
		"c",
		"kjxhwupoxpqtcgafzyxmceippseyqwowdgxacppmwljsreiqwk",
		"k",
		"vb",
		"df",
		"sq",
		"ou",
		"pc",
		"tn",
		"yg",
		"eg",
		"wt",
		"je",
		"mt",
		"vi",
		"ob",
		"wu",
		"os",
		"atlqerdjdszzmyqwutkcixujbnymgpjrssmadscnxokzbvalge",
		"ac",
		"xo",
		"cm",
		"za",
		"im",
		"gu",
		"jnwpdxbterxxgqsifspvhtjkrrjrzsbkmkjpbxgtvxghaeovem",
		"nb",
		"hp",
		"fhguuzpuricbknarvfvuuaiqjuoneprtedxhokkoomnpyzrffk",
		"ze",
		"oc",
		"xb",
		"o",
		"hc",
		"yy",
		"qw",
		"hv",
		"sc",
		"bx",
		"ci",
		"ax",
		"sx",
		"uh",
		"au",
		"ut",
		"ld",
		"y",
		"x",
		"eu",
		"kn",
		"go",
		"pz",
		"hk",
		"nl",
		"po",
		"mc",
		"ivhfelbyrrdjtxtdilqhhxpwyeuusgrrewzggafnkwqxdhwqnp",
		"lfprlmqoqyaidlggysrjvraskrfaihsvnlojvcxdkxwqsujmmc",
		"b",
		"aq",
		"ti",
		"ar",
		"vqtrekspbphuhdjmvbrbrsbjnwxwefsaujonueezvgsgwshctk",
		"jdjikdnrfuynqdenupurxwwxvdrenuwznduourgrkfzwxsucob",
		"p",
		"hjzxxhlvpmrdcgomiaydnmmkqyrawxhczldrdmqhzzmslpfzvz",
		"dr",
		"vs",
		"cv",
		"zg",
		"on",
		"yf",
		"pa",
		"gupimkaxzmfktkzdctinmhlimdfcxhipsmdoluodlbvkyhcmki",
		"flbabfhawdaqlwvpcstuikgcjkdqknfcmopnqtvpussgflmeqb",
		"f",
		"oy",
		"sr",
		"reoukvhpfgzkdsimjuifwmyrybmwmuoavkfdsijwlugjhyfimd",
		"xsqxmaanlrljzihrgpguewkbqksrzhgkonlbfpmudiubernymq",
		"kveomwtmyfyfnucdcphwqfmmmifhibnbogbwzazulbqbstbrzk",
		"h",
		"or",
		"tk",
		"xm",
		"ex",
		"og",
		"lt",
		"q",
		"e",
		"ykypmlotoztrgvwnpxuzhvawbkterpdbjcmtbamvgeahgzdgsq",
		"xa",
		"na",
		"zp",
		"qa",
		"ru",
		"sd",
		"gv",
		"zupodigekkqqpzxzgqvzziejimhrbokysmuhsafjpjbwktnuhl",
		"jjutatmjaydqkppqzmlvpgqpuowfkdqblyipivdvmzjrtskdlu",
		"iz",
		"yd",
		"sk",
		"vk",
		"rx",
		"hg",
		"gk",
		"hr",
		"ekciqajslpdscierruoyuguajljprqvtknplayirfsdjqfpidw",
		"om",
		"ub",
		"xd",
		"km",
		"ez",
		"he",
		"dx",
		"ig",
		"id",
		"pd",
		"qhegnofrraudcxwzdfxmheaersybvxpgocgsazukleuvafpmuj",
		"wa",
		"qt",
		"cw",
		"no",
		"lp",
		"wb",
		"ql",
		"yzkahsewrhfriyjbbuwnaaglygppsstpqfgifsfeakptocpsfj",
		"wi",
		"iu",
		"bo",
		"ge",
		"gh",
		"cf",
		"wf",
		"qemoqpltvoneqrgrmtouakbuonlcnfmfmheuicsasqwhmorwvf",
		"gm",
		"ie",
		"rh",
		"a",
		"pi",
		"rkilafbvqwenffovvgebfpnqdtqjxfqtmygaimsrxratvuqqxk",
		"nd",
		"pu",
		"vz",
		"uo",
		"rb",
		"fs",
		"yoprekcfrmetsdrkjinmhhdpkmcqmvtgkaqknvbpcbhgmsqehe",
		"opekcclbtawwhvemtmstzalhfkjhxbavgagjmlgwhqktcoosst",
		"bf",
		"wzsymzwxkbkgjxziqhxezkfyfmlmtcaphqxmfdlucocftlgkdj",
		"ud",
		"fq",
		"ur",
		"vd",
		"nq",
		"nzavtdsdxafxrihxsuaxnkcslohgevipbqivtpmiipaprvukfp",
		"fr",
		"bi",
		"obcrtojfysapvcpmfpchrypkvcwbfszaoivkbaoruftxblklmj",
		"zd",
		"oe",
		"nw",
		"dh",
		"yc",
		"jo",
		"vkgsqujvizliryrtqbugstjizernuxctirsvcfeqdkvlwpvsad",
		"jr",
		"br",
		"samdncvzklkbpqpkitzikypiiumlahfwsjacywxxidckgqnfgc",
		"ok",
		"fv",
		"rj",
		"ed",
		"qx",
		"oz",
		"bq",
		"fhlpatrkdqzpvcedjrjdutdcurwiencuimpkkjtcjwkoqtlpep",
		"uc",
		"tb",
		"ts",
		"es",
		"vg",
		"lx",
		"lv",
		"oi",
		"tt",
		"zr",
		"zo",
		"eriudaxijfznacglrhtxyyhkdhqzqqpcnofyrsddmioknzlerm",
		"jm",
		"jb",
		"od",
		"hm",
		"qy",
		"klmzkhdjqkvibelzkgzjdxzqeqznfpmerbezfhofbpsxuxqzrw",
		"ua",
		"vm",
		"mk",
		"hb",
		"zy",
		"pm",
		"iw",
		"dc",
		"la",
		"vp",
		"zl",
		"lqkylbwdmirzskccrhfwspqrpqbwedwgrjixgyiqtelguguepv",
		"zxhaiovtaskhvywxxxsvkwqujfmknklpondzwovuhwnszwkrvn",
		"jv",
		"fm",
		"ps",
		"wz",
		"jq",
		"sv",
		"vh",
		"nv",
		"pqovwnffwqsgdhnsckeqmbuhdlqwpkglwqbpbsrkxpfbanitsm",
		"ia",
		"jy",
		"vw",
		"lz",
		"nj",
		"uq",
		"hs",
		"wp",
		"qf",
		"se",
		"qe",
		"ab",
		"yi",
		"hhblsevefjnqeekzdyjuvubhifusxmqqngpcssobiabmjevvkp",
		"dp",
		"dfedkaivixvydogxxiqftbpzjesmjtilwitumfpxrjpmllymwe",
		"vf",
		"ol",
		"qn",
		"sw",
		"bc",
		"oq",
		"ky",
		"il",
		"tv",
		"xj",
		"zz",
		"eo",
		"vt",
		"bd",
		"md",
		"xg",
		"copaksgibhlhkpqxsugbseomulcglhkvgidgecmnemtfqcxcqb",
		"zq",
		"fp",
		"ff",
		"yv",
		"qo",
		"tm",
		"kv",
		"eqmjuybpsfxmbypqeovnmuhqsslparumvkvkrzkgomvgoanalt",
		"yj",
		"et",
		"adzxwpqbkythwjrjeqnjxtfiviyscvbymxquwhnkmjbwocxkzu",
		"pr",
		"lm",
		"lf",
		"ue",
		"xe",
		"lq",
		"kb",
		"kl",
		"ba",
		"cc",
		"nk",
		"nx",
		"sz",
		"jn",
		"ei",
		"nn",
		"uy",
		"an",
		"hi",
		"yz",
		"fa",
		"zi",
		"xt",
		"ji",
		"yh",
		"xl",
		"qm",
		"cr",
		"yl",
		"mq",
		"rt",
		"pl",
		"cp",
		"cs",
		"fz",
		"ug",
		"lr",
		"zikimyhqdalrwsxgagetoaofqlvmjlomwpkrnzurpmswuylhaq",
		"dqkswyrkfhjmezwxqvqwkbqjgqjfnwmmxrbfglmkmjbdzuzcsa",
		"oo",
		"lk",
		"tf",
		"pg",
		"cl",
		"yo",
		"ww",
		"vj",
		"u",
		"le",
		"ca",
		"kh",
		"gg",
		"mvgkxfembpprqvyantbskhbycclvnwmeskguxlmeceqraqpbci",
		"gq",
		"qb",
		"jw",
		"kc",
		"ej",
		"bp",
		"qq",
		"ov",
		"fh",
		"we",
		"vn",
		"jp",
		"ah",
		"me",
		"fx",
		"cx",
		"l",
		"ko",
		"wr",
		"tj",
		"fdrgfycjxzruwaanmyhaohwlfypvmkpqxzknhbpwbnwyhghzls",
		"mg",
		"my",
		"ziuibvhguhwziomtxbleugfaigpgmduvhfdxbvvvgeoagxsllp",
		"ai",
		"tbqtjiwwqftmhwwvauzzicybdvulksastulcquuokpqerpgqje",
		"gc",
		"zv",
		"taxyfiiyapfnqaifvahxmsgcorihsildysshgbxucxmogouwtl",
		"tfgeigfqowcgnoxyutsnsrymkoshyeeuzvluujkuiotpjopqgj",
		"bycdykpmtsryetqzsblkjfzuxwczpthgyclhlxhcmpevnrnmhp",
		"dl",
		"qi",
		"oh",
		"ht",
		"wx",
		"is",
		"sg",
		"wq",
		"ix",
		"of",
		"pk",
		"sh",
		"zwbenudxmnnseibttpybkxmakarngnkoeqdeifaxvfebaospkx",
		"zc",
		"hd",
		"bj",
		"hh",
		"vtzizanfmdkxklnuxloiqvsqplivyyvxvcpnucyoxedlacatwe",
		"gy",
		"ot",
		"oj",
		"fy",
		"pn",
		"mj",
		"dk",
		"vx",
		"fc",
		"pw",
		"kz",
		"ss",
		"ys",
		"ow",
		"ec",
		"al",
		"cq",
		"xv",
		"de",
		"zh",
		"w",
		"zn",
		"mb",
		"ay",
		"ek",
		"td",
		"cbnvjoixfeuupomhqjjktmfmfaawxkrveqvpvjkrdlptyellac",
		"kt",
		"qh",
		"fd",
		"ft",
		"ma",
		"qd",
		"dt",
		"wc",
		"zx",
		"szsuhmftaarehqcnsmtxnciptadokmohhguizcbxmuihxajnou",
		"rg",
		"ew",
		"qr",
		"rr",
		"ndqobdpgnjahrnaorbgrubqxpgiabnxwkymjvpgezlvsnvyxpe",
		"re",
		"tp",
		"ag",
		"ki",
		"pf",
		"gl",
		"ks",
		"fw",
		"gt",
		"ep",
		"j",
		"ga",
		"tvberqlfknpumimdglrjhoaocuyabqtznoewsderntuvdcpymd",
		"swbdzkzikrulrmxpiaukijfxlvrxmwdojsudqftfzlwehkeddd",
		"rp",
		"sb",
		"di",
		"um",
		"fu",
		"hl",
		"djgbkaciyeracnpljhpqhjbpdlqcdfhovlhaignnaihbfuiskr",
		"dv",
		"op",
		"g",
		"ui",
		"ry",
		"sj",
		"ik",
		"bn",
		"af",
		"mf",
		"cn",
		"xs",
		"qs" };
	cout << sol.maxRectangle(words) << endl;

	words = { "this", "real", "hard", "trh", "hea", "iar", "sld" };
	cout << sol.maxRectangle(words) << endl;

	words = { "aa" };
	cout << sol.maxRectangle(words) << endl;
}