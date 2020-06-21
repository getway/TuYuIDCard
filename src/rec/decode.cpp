// Copyright(c) TuYuAI authors.All rights reserved.
// Licensed under the Apache-2.0 License.
//

#include "decode.h"

std::vector<int> GreedyDecode(const std::vector<int> &preds) {
  std::vector<int> res;
  int preds_size = preds.size();
  for (int i = 0; i < preds_size; i++) {
    if (preds[i] != 0 && !(i > 0 && preds[i - 1] == preds[i])) {
      res.push_back(preds[i]);
    }
  }
  return res;
}

std::vector<std::string> alphabets = {
    " ",  "!",  "\"", "#",  "$",  "%",  "&",  "\'", "(",  ")",  "*",  "+",
    ",",  "-",  ".",  "/",  "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",
    "8",  "9",  ":",  ";",  "<",  "=",  ">",  "?",  "@",  "A",  "B",  "C",
    "D",  "E",  "F",  "G",  "H",  "I",  "J",  "K",  "L",  "M",  "N",  "O",
    "P",  "Q",  "R",  "S",  "T",  "U",  "V",  "W",  "X",  "Y",  "Z",  "[",
    "\\", "]",  "^",  "_",  "`",  "a",  "b",  "c",  "d",  "e",  "f",  "g",
    "h",  "i",  "j",  "k",  "l",  "m",  "n",  "o",  "p",  "q",  "r",  "s",
    "t",  "u",  "v",  "w",  "x",  "y",  "z",  "{",  "|",  "}",  "~",  "°",
    "±",  "·",  "×",  "à",  "é",  "÷",  "ü",  "α",  "β",  "О",  "П",  "Р",
    "–",  "—",  "―",  "‘",  "’",  "“",  "”",  "…",  "‰",  "′",  "※",  "℃",
    "Ⅰ",  "Ⅱ",  "Ⅲ",  "Ⅳ",  "→",  "↓",  "∈",  "√",  "∩",  "∵",  "∶",  "≠",
    "≤",  "≥",  "①",  "②",  "③",  "④",  "⑤",  "⑥",  "⑦",  "⑧",  "⑨",  "⑩",
    "⑴",  "⑵",  "⑶",  "⑾",  "⑿",  "⒀",  "⒂",  "⒃",  "⒄",  "⒅",  "⒆",  "⒈",
    "⒉",  "⒊",  "─",  "━",  "│",  "┌",  "┐",  "╱",  "■",  "□",  "▲",  "△",
    "◆",  "◇",  "○",  "◎",  "●",  "★",  "☆",  "　", "、", "。", "〇", "〈",
    "〉", "《", "》", "「", "」", "『", "』", "【", "】", "〔", "〕", "て",
    "な", "㘰", "㘵", "㙍", "㙟", "䓣", "䶮", "一", "丁", "七", "万", "丈",
    "三", "上", "下", "不", "与", "丐", "丑", "专", "且", "丕", "世", "丘",
    "丙", "业", "丛", "东", "丝", "丞", "丢", "两", "严", "丧", "个", "丫",
    "中", "丰", "串", "临", "丸", "丹", "为", "主", "丽", "举", "乂", "乃",
    "久", "么", "义", "之", "乌", "乍", "乎", "乏", "乐", "乒", "乓", "乔",
    "乖", "乘", "乙", "乜", "九", "乞", "也", "习", "乡", "书", "乩", "买",
    "乱", "乳", "乸", "乾", "了", "予", "争", "事", "二", "于", "亏", "云",
    "互", "亓", "五", "井", "亘", "亚", "些", "亟", "亡", "亢", "交", "亥",
    "亦", "产", "亨", "亩", "享", "京", "亭", "亮", "亲", "亳", "亵", "亶",
    "人", "亿", "什", "仁", "仂", "仃", "仄", "仅", "仆", "仇", "仉", "今",
    "介", "仍", "从", "仑", "仓", "仔", "仕", "他", "仗", "付", "仙", "仚",
    "仝", "仞", "仟", "仡", "代", "令", "以", "仨", "仪", "仫", "们", "仰",
    "仲", "仵", "件", "价", "任", "份", "仿", "企", "伉", "伊", "伍", "伎",
    "伏", "伐", "休", "伕", "众", "优", "伙", "会", "伛", "伞", "伟", "传",
    "伢", "伤", "伦", "伧", "伪", "伫", "伯", "估", "伲", "伴", "伶", "伸",
    "伺", "伻", "似", "伽", "伾", "佀", "佃", "但", "佈", "位", "低", "住",
    "佐", "佑", "体", "何", "佗", "佘", "余", "佚", "佛", "作", "佝", "佞",
    "佟", "你", "佣", "佤", "佧", "佩", "佬", "佯", "佰", "佳", "佴", "佶",
    "佺", "佻", "佼", "佾", "使", "侃", "侄", "侈", "侉", "例", "侍", "侏",
    "侑", "侔", "侗", "供", "依", "侠", "侣", "侥", "侦", "侧", "侨", "侩",
    "侪", "侬", "侮", "侯", "侴", "侵", "便", "促", "俄", "俅", "俊", "俍",
    "俎", "俏", "俐", "俑", "俗", "俘", "俚", "俛", "保", "俞", "俟", "信",
    "俣", "俤", "俦", "俨", "俩", "俪", "俬", "俭", "修", "俯", "俱", "俳",
    "俵", "俶", "俸", "俺", "俾", "倍", "倏", "倒", "倓", "倔", "倖", "倘",
    "候", "倚", "倜", "倞", "借", "倡", "倢", "倦", "倨", "倩", "倪", "倬",
    "倭", "倮", "倴", "债", "值", "倾", "偃", "假", "偈", "偌", "偎", "偏",
    "偕", "做", "停", "健", "偰", "偲", "偶", "偷", "偻", "偿", "傀", "傅",
    "傈", "傍", "傑", "傕", "傢", "傣", "傥", "傧", "储", "傩", "催", "傲",
    "傻", "像", "僖", "僚", "僦", "僧", "僭", "僮", "僰", "僳", "僵", "價",
    "僻", "儀", "億", "儆", "儇", "儋", "儒", "儡", "儿", "兀", "允", "元",
    "兄", "充", "兆", "先", "光", "克", "免", "兑", "兒", "兔", "兕", "兖",
    "党", "兜", "兢", "入", "內", "全", "八", "公", "六", "兮", "兰", "共",
    "关", "兴", "兵", "其", "具", "典", "兹", "养", "兼", "兽", "冀", "冁",
    "内", "冈", "冉", "册", "再", "冏", "冑", "冒", "冕", "冗", "写", "冚",
    "军", "农", "冠", "冢", "冤", "冥", "冬", "冮", "冯", "冰", "冲", "决",
    "况", "冶", "冷", "冻", "冼", "冽", "净", "凃", "凄", "准", "凇", "凉",
    "凋", "凌", "凎", "减", "凑", "凛", "凝", "几", "凡", "凤", "凫", "凭",
    "凯", "凰", "凱", "凳", "凶", "凸", "凹", "出", "击", "凼", "函", "凿",
    "刀", "刁", "刃", "分", "切", "刈", "刊", "刍", "刎", "刑", "划", "刓",
    "刖", "列", "刘", "则", "刚", "创", "初", "删", "判", "刨", "利", "别",
    "刭", "刮", "到", "刳", "制", "刷", "券", "刹", "刺", "刻", "刽", "剀",
    "剁", "剂", "剃", "剅", "削", "剌", "前", "剎", "剐", "剑", "剔", "剖",
    "剜", "剡", "剥", "剧", "剩", "剪", "副", "割", "剽", "剿", "劈", "劓",
    "劙", "力", "劝", "办", "功", "加", "务", "劢", "劣", "劦", "动", "助",
    "努", "劫", "劬", "劭", "励", "劲", "劳", "劵", "劼", "劾", "势", "勃",
    "勇", "勉", "勋", "勍", "勐", "勒", "勖", "勘", "募", "勤", "勰", "勺",
    "勾", "勿", "匀", "包", "匆", "匈", "匍", "匏", "匐", "匕", "化", "北",
    "匙", "匝", "匠", "匡", "匣", "匪", "匮", "匳", "匹", "区", "医", "匽",
    "匾", "匿", "區", "十", "千", "卅", "升", "午", "卉", "半", "华", "协",
    "卑", "卒", "卓", "单", "卖", "南", "博", "卜", "卞", "占", "卡", "卢",
    "卤", "卦", "卧", "卫", "卬", "卮", "卯", "印", "危", "即", "却", "卵",
    "卷", "卸", "卺", "卿", "厂", "厄", "厅", "历", "厉", "压", "厌", "厍",
    "厐", "厕", "厘", "厚", "厝", "原", "厢", "厥", "厦", "厨", "厩", "厮",
    "厶", "去", "县", "叁", "参", "又", "叉", "及", "友", "双", "反", "发",
    "叔", "取", "受", "变", "叙", "叛", "叟", "叠", "叡", "口", "古", "句",
    "另", "叨", "叩", "只", "叫", "召", "叭", "叮", "可", "台", "叱", "史",
    "右", "叵", "叶", "号", "司", "叹", "叻", "叼", "叽", "吁", "吃", "各",
    "吆", "合", "吉", "吊", "同", "名", "后", "吏", "吐", "向", "吒", "吓",
    "吕", "吗", "君", "吝", "吞", "吟", "吠", "否", "吧", "吨", "吩", "含",
    "听", "吭", "吮", "启", "吱", "吴", "吵", "吸", "吹", "吻", "吼", "吾",
    "呀", "呂", "呃", "呆", "呈", "告", "呐", "呓", "呕", "呗", "员", "呙",
    "呛", "呜", "呢", "呤", "呦", "周", "呱", "味", "呵", "呶", "呷", "呻",
    "呼", "命", "咀", "咂", "咄", "咆", "咋", "和", "咎", "咏", "咐", "咒",
    "咔", "咕", "咖", "咘", "咙", "咚", "咛", "咡", "咣", "咤", "咦", "咧",
    "咨", "咪", "咫", "咬", "咯", "咱", "咳", "咸", "咻", "咽", "咿", "哀",
    "品", "哂", "哄", "哆", "哇", "哈", "哉", "哌", "响", "哎", "哏", "哑",
    "哓", "哗", "哙", "哝", "哟", "哥", "哦", "哧", "哨", "哩", "哪", "哭",
    "哮", "哲", "哺", "哼", "哽", "哿", "唁", "唆", "唇", "唉", "唏", "唐",
    "唑", "唔", "唕", "唛", "唠", "唢", "唤", "唧", "唬", "售", "唯", "唱",
    "唳", "唶", "唸", "唾", "唿", "啁", "啃", "啄", "商", "啊", "啐", "啓",
    "啕", "啖", "啜", "啟", "啡", "啤", "啥", "啦", "啧", "啪", "啬", "啮",
    "啰", "啶", "啸", "啻", "啼", "啾", "喀", "喁", "喂", "喃", "善", "喆",
    "喇", "喉", "喊", "喋", "喏", "喑", "喔", "喘", "喙", "喜", "喝", "喟",
    "喧", "喱", "喳", "喷", "喹", "喻", "喽", "喾", "嗄", "嗅", "嗌", "嗑",
    "嗒", "嗓", "嗔", "嗖", "嗛", "嗜", "嗝", "嗟", "嗡", "嗣", "嗤", "嗥",
    "嗦", "嗨", "嗪", "嗫", "嗯", "嗲", "嗳", "嗷", "嗽", "嗾", "嘀", "嘈",
    "嘉", "嘌", "嘎", "嘘", "嘛", "嘟", "嘡", "嘤", "嘭", "嘱", "嘲", "嘴",
    "嘶", "嘹", "嘻", "嘿", "噉", "噌", "噎", "噔", "噗", "噙", "噜", "噢",
    "噤", "器", "噩", "噪", "噫", "噬", "噭", "噱", "噶", "噻", "嚅", "嚎",
    "嚏", "嚓", "嚣", "嚬", "嚷", "嚼", "囊", "囔", "囗", "囚", "四", "囝",
    "回", "因", "囡", "团", "囤", "囫", "园", "困", "囱", "围", "囵", "囷",
    "囹", "固", "国", "图", "囿", "圃", "圄", "圆", "圈", "圉", "國", "圐",
    "園", "圓", "團", "圙", "圜", "土", "圣", "在", "圩", "圪", "圭", "圯",
    "地", "圳", "圹", "场", "圻", "圾", "址", "坁", "坂", "均", "坉", "坊",
    "坌", "坍", "坎", "坏", "坐", "坑", "块", "坚", "坛", "坜", "坝", "坞",
    "坟", "坠", "坡", "坣", "坤", "坦", "坨", "坪", "坬", "坭", "坮", "坯",
    "坳", "坵", "坷", "坻", "坼", "坽", "垂", "垃", "垄", "垅", "垆", "垇",
    "垈", "型", "垌", "垒", "垓", "垕", "垚", "垛", "垝", "垞", "垟", "垠",
    "垡", "垢", "垣", "垤", "垦", "垧", "垩", "垫", "垭", "垮", "垯", "垱",
    "垲", "垴", "垵", "垸", "垾", "垿", "埂", "埃", "埇", "埋", "埌", "城",
    "埒", "埔", "埕", "埗", "埙", "埚", "埜", "埝", "域", "埠", "埡", "埤",
    "埩", "埪", "埫", "埭", "埸", "培", "基", "埼", "堀", "堂", "堃", "堆",
    "堇", "堉", "堋", "堌", "堍", "堎", "堑", "堕", "堘", "堙", "堞", "堠",
    "堡", "堤", "堪", "堯", "堰", "報", "場", "堵", "堼", "堽", "塄", "塅",
    "塆", "塌", "塍", "塑", "塔", "塘", "塚", "塝", "塞", "塥", "塨", "填",
    "塬", "塭", "塱", "塽", "塾", "墀", "墁", "境", "墅", "墈", "墉", "墓",
    "墕", "墘", "墙", "增", "墟", "墠", "墨", "墩", "壁", "壅", "壆", "壑",
    "壕", "壘", "壤", "士", "壬", "壮", "声", "壳", "壶", "壹", "壽", "处",
    "夆", "备", "复", "夏", "夔", "夕", "外", "夙", "多", "夜", "够", "夤",
    "夥", "大", "天", "太", "夫", "夭", "央", "夯", "失", "头", "夷", "夸",
    "夹", "夺", "夼", "奀", "奁", "奂", "奄", "奇", "奈", "奉", "奋", "奎",
    "奏", "契", "奓", "奔", "奕", "奖", "套", "奘", "奚", "奠", "奡", "奢",
    "奥", "奭", "女", "奴", "奶", "奸", "她", "好", "妁", "如", "妃", "妄",
    "妆", "妇", "妈", "妊", "妍", "妒", "妓", "妖", "妗", "妙", "妞", "妤",
    "妥", "妨", "妩", "妪", "妮", "妲", "妳", "妹", "妻", "妾", "姁", "姆",
    "姊", "始", "姐", "姑", "姒", "姓", "委", "姗", "姚", "姜", "姝", "姣",
    "姥", "姨", "姬", "姮", "姹", "姻", "姿", "威", "娃", "娄", "娅", "娆",
    "娇", "娈", "娉", "娌", "娑", "娒", "娓", "娘", "娜", "娟", "娠", "娡",
    "娣", "娥", "娩", "娱", "娲", "娴", "娶", "娼", "婀", "婆", "婉", "婊",
    "婍", "婕", "婚", "婢", "婧", "婪", "婳", "婴", "婵", "婶", "婷", "婺",
    "婻", "婼", "婿", "媒", "媖", "媗", "媚", "媛", "媞", "媪", "媲", "媳",
    "媵", "媸", "媾", "嫁", "嫂", "嫄", "嫉", "嫌", "嫒", "嫔", "嫖", "嫘",
    "嫚", "嫜", "嫡", "嫣", "嫦", "嫩", "嫪", "嫱", "嬉", "嬌", "嬖", "嬗",
    "嬛", "嬴", "嬿", "孀", "子", "孑", "孔", "孕", "字", "存", "孙", "孚",
    "孛", "孜", "孝", "孟", "孢", "季", "孤", "孥", "学", "孩", "孪", "孬",
    "孰", "孱", "孳", "孵", "孺", "孽", "宁", "它", "宅", "宇", "守", "安",
    "宋", "完", "宏", "宓", "宕", "宗", "官", "宙", "定", "宛", "宜", "宝",
    "实", "宠", "审", "客", "宣", "室", "宥", "宦", "宪", "宫", "宬", "宰",
    "害", "宴", "宵", "家", "宸", "容", "宽", "宾", "宿", "寀", "寂", "寄",
    "寅", "密", "寇", "富", "寐", "寒", "寓", "寖", "寘", "寝", "寞", "察",
    "寡", "寤", "寥", "寧", "寨", "寮", "寰", "寸", "对", "寺", "寻", "导",
    "寿", "封", "射", "将", "尉", "尊", "對", "小", "少", "尔", "尕", "尖",
    "尘", "尚", "尝", "尤", "尧", "尬", "就", "尴", "尸", "尹", "尺", "尻",
    "尼", "尽", "尾", "尿", "局", "屁", "层", "居", "屈", "屉", "届", "屋",
    "屎", "屏", "屐", "屑", "展", "属", "屠", "屡", "屣", "層", "履", "屦",
    "屯", "山", "屲", "屹", "屺", "屾", "屿", "岁", "岂", "岈", "岌", "岐",
    "岑", "岔", "岕", "岖", "岗", "岘", "岙", "岚", "岛", "岜", "岞", "岢",
    "岣", "岩", "岫", "岬", "岭", "岱", "岳", "岵", "岷", "岸", "岺", "岽",
    "岿", "峁", "峃", "峄", "峇", "峋", "峒", "峗", "峘", "峙", "峡", "峣",
    "峤", "峥", "峦", "峨", "峪", "峭", "峯", "峰", "峻", "崀", "崂", "崃",
    "崆", "崇", "崎", "崑", "崔", "崖", "崗", "崙", "崚", "崛", "崞", "崟",
    "崤", "崧", "崩", "崭", "崮", "崯", "崴", "崽", "崾", "嵅", "嵇", "嵊",
    "嵋", "嵌", "嵖", "嵘", "嵚", "嵛", "嵝", "嵩", "嵬", "嵯", "嵿", "嶂",
    "嶍", "嶒", "嶙", "嶚", "嶝", "嶷", "嶺", "巅", "巉", "巍", "川", "州",
    "巡", "巢", "工", "左", "巧", "巨", "巩", "巫", "差", "己", "已", "巳",
    "巴", "巷", "巽", "巾", "巿", "币", "市", "布", "帅", "帆", "师", "希",
    "帏", "帐", "帑", "帔", "帕", "帖", "帘", "帚", "帛", "帜", "帝", "带",
    "帧", "帨", "席", "帮", "帷", "常", "帼", "帽", "幂", "幄", "幅", "幌",
    "幔", "幕", "幛", "幞", "幡", "幢", "干", "平", "年", "并", "幸", "幺",
    "幻", "幼", "幽", "广", "庄", "庆", "庇", "床", "序", "庐", "庑", "库",
    "应", "底", "庖", "店", "庙", "庚", "府", "庞", "废", "庠", "庥", "度",
    "座", "庭", "庵", "庶", "康", "庸", "庹", "庾", "廉", "廊", "廒", "廓",
    "廖", "廛", "廣", "廨", "廪", "延", "廷", "建", "廿", "开", "弁", "异",
    "弃", "弄", "弇", "弈", "弊", "弋", "式", "弑", "弓", "引", "弗", "弘",
    "弛", "弟", "张", "弢", "弥", "弦", "弧", "弨", "弩", "弭", "弯", "弱",
    "張", "弶", "弹", "强", "弼", "彀", "彊", "彐", "归", "当", "录", "彗",
    "彘", "彝", "形", "彤", "彦", "彧", "彩", "彪", "彬", "彭", "彰", "影",
    "彷", "役", "彻", "彼", "彿", "往", "征", "徂", "径", "待", "徇", "很",
    "徉", "徊", "律", "後", "徐", "徒", "徕", "得", "徘", "徙", "徜", "御",
    "徨", "循", "徭", "微", "徳", "徵", "德", "徼", "徽", "心", "必", "忆",
    "忌", "忍", "忏", "忐", "忑", "忒", "忖", "志", "忘", "忙", "忝", "忞",
    "忠", "忡", "忤", "忧", "忪", "快", "忱", "念", "忻", "忽", "忿", "怀",
    "态", "怂", "怅", "怆", "怍", "怎", "怏", "怒", "怔", "怕", "怖", "怙",
    "怛", "怜", "思", "怠", "怡", "急", "怦", "性", "怨", "怪", "怫", "怯",
    "怵", "总", "怼", "怿", "恂", "恃", "恋", "恍", "恐", "恒", "恕", "恙",
    "恚", "恝", "恢", "恣", "恤", "恨", "恩", "恪", "恫", "恬", "恭", "息",
    "恰", "恳", "恶", "恸", "恹", "恺", "恻", "恼", "恽", "恿", "悃", "悄",
    "悅", "悉", "悌", "悍", "悒", "悔", "悖", "悚", "悝", "悞", "悟", "悠",
    "患", "悦", "您", "悫", "悬", "悭", "悯", "悲", "悴", "悸", "悻", "悼",
    "情", "惆", "惇", "惊", "惋", "惑", "惕", "惘", "惚", "惜", "惟", "惠",
    "惦", "惧", "惨", "惩", "惫", "惬", "惭", "惮", "惯", "惰", "想", "惴",
    "惶", "惹", "惺", "愀", "愁", "愆", "愈", "愉", "愍", "愎", "意", "愔",
    "愕", "愚", "愛", "感", "愠", "愣", "愤", "愦", "愧", "愫", "愬", "愷",
    "愿", "慈", "慊", "慌", "慎", "慑", "慕", "慙", "慜", "慢", "慧", "慨",
    "慰", "慵", "慷", "憋", "憎", "憔", "憧", "憨", "憩", "憬", "憶", "憾",
    "懂", "懈", "懊", "懋", "懑", "懒", "懜", "懦", "懵", "懿", "戆", "戈",
    "戊", "戌", "戍", "戎", "戏", "成", "我", "戒", "戕", "或", "戗", "战",
    "戚", "戛", "戟", "戡", "戢", "戥", "截", "戬", "戮", "戳", "戴", "户",
    "戾", "房", "所", "扁", "扃", "扆", "扇", "扈", "扉", "手", "扌", "才",
    "扎", "扑", "扒", "打", "扔", "托", "扛", "扞", "扢", "扣", "执", "扩",
    "扪", "扫", "扬", "扭", "扮", "扯", "扰", "扳", "扶", "批", "扼", "找",
    "承", "技", "抄", "抉", "把", "抑", "抒", "抓", "投", "抖", "抗", "折",
    "抚", "抛", "抟", "抠", "抡", "抢", "护", "报", "抨", "披", "抬", "抱",
    "抵", "抹", "抻", "押", "抽", "抿", "拂", "拄", "担", "拆", "拇", "拈",
    "拉", "拊", "拌", "拍", "拎", "拐", "拑", "拒", "拓", "拔", "拖", "拗",
    "拘", "拙", "拚", "招", "拜", "拟", "拢", "拣", "拥", "拦", "拧", "拨",
    "择", "括", "拭", "拮", "拯", "拱", "拳", "拴", "拷", "拼", "拽", "拾",
    "拿", "持", "挂", "指", "挈", "按", "挎", "挑", "挖", "挚", "挛", "挝",
    "挞", "挟", "挠", "挡", "挣", "挤", "挥", "挨", "挪", "挫", "振", "挹",
    "挺", "挽", "捂", "捅", "捆", "捉", "捋", "捌", "捍", "捎", "捏", "捐",
    "捕", "捞", "损", "捡", "换", "捣", "捧", "捭", "据", "捱", "捶", "捷",
    "捺", "捻", "捽", "掀", "掂", "掇", "授", "掉", "掌", "掏", "掐", "排",
    "掖", "掘", "掛", "掠", "探", "掣", "接", "控", "推", "掩", "措", "掬",
    "掰", "掳", "掷", "掺", "掼", "掾", "揄", "揆", "揉", "揍", "描", "提",
    "插", "揖", "揜", "握", "揣", "揩", "揪", "揭", "援", "揶", "揽", "搀",
    "搁", "搂", "搅", "搌", "搏", "搐", "搒", "搓", "搔", "搜", "搞", "搠",
    "搢", "搪", "搬", "搭", "搴", "携", "搽", "摁", "摄", "摆", "摇", "摈",
    "摊", "摒", "摔", "摘", "摞", "摧", "摩", "摸", "摹", "撂", "撇", "撑",
    "撒", "撕", "撖", "撝", "撞", "撤", "撩", "撬", "播", "撮", "撰", "撵",
    "撷", "撺", "撼", "擀", "擂", "擅", "操", "擎", "擒", "擘", "擞", "擢",
    "擦", "攀", "攒", "攘", "攥", "攫", "支", "收", "攸", "改", "攻", "放",
    "政", "故", "效", "敉", "敌", "敏", "救", "敕", "敖", "教", "敛", "敝",
    "敞", "敢", "散", "敦", "敬", "数", "敲", "整", "敷", "文", "斋", "斌",
    "斐", "斑", "斓", "斗", "料", "斛", "斜", "斟", "斡", "斤", "斥", "斧",
    "斩", "斫", "断", "斯", "新", "斲", "方", "於", "施", "旁", "旃", "旄",
    "旅", "旆", "旋", "旌", "旎", "族", "旒", "旖", "旗", "无", "既", "日",
    "旦", "旧", "旨", "早", "旬", "旭", "旮", "旯", "旱", "旴", "旵", "时",
    "旷", "旸", "旺", "旻", "旼", "昀", "昂", "昃", "昆", "昇", "昉", "昊",
    "昌", "明", "昏", "易", "昔", "昕", "昙", "昝", "昞", "星", "映", "春",
    "昧", "昨", "昫", "昭", "是", "昰", "昱", "昳", "昴", "昵", "昶", "昺",
    "昼", "显", "晁", "晃", "晅", "晉", "晋", "晌", "晏", "晒", "晓", "晔",
    "晕", "晖", "晗", "晚", "晛", "晞", "晟", "晡", "晢", "晤", "晦", "晧",
    "晨", "普", "景", "晰", "晴", "晶", "晸", "晹", "智", "晾", "暂", "暄",
    "暇", "暐", "暑", "暕", "暖", "暗", "暘", "暠", "暧", "暨", "暮", "暲",
    "暴", "暹", "暾", "曈", "曌", "曙", "曚", "曛", "曜", "曝", "曦", "曩",
    "曰", "曲", "曳", "更", "曷", "書", "曹", "曼", "曾", "替", "最", "朂",
    "會", "月", "有", "朋", "服", "朐", "朔", "朕", "朗", "望", "朝", "期",
    "朦", "木", "未", "末", "本", "札", "术", "朱", "朴", "朵", "机", "朽",
    "杀", "杂", "权", "杆", "杈", "杉", "杌", "李", "杏", "材", "村", "杓",
    "杖", "杜", "杞", "束", "杠", "条", "来", "杨", "杪", "杭", "杯", "杰",
    "東", "杲", "杳", "杵", "杷", "杼", "松", "板", "极", "构", "枇", "枉",
    "枋", "析", "枕", "林", "枘", "枚", "果", "枝", "枞", "枢", "枣", "枥",
    "枧", "枨", "枪", "枫", "枭", "枯", "枰", "枳", "枵", "架", "枷", "枸",
    "枹", "柃", "柄", "柈", "柏", "某", "柑", "柒", "染", "柔", "柘", "柚",
    "柜", "柞", "柠", "柢", "查", "柩", "柬", "柯", "柰", "柱", "柳", "柴",
    "柽", "柿", "栀", "栅", "标", "栈", "栉", "栊", "栋", "栎", "栏", "树",
    "栒", "栓", "栖", "栗", "栟", "校", "栢", "栩", "株", "栲", "栳", "样",
    "核", "根", "格", "栽", "栾", "栿", "桀", "桁", "桂", "桃", "桄", "桅",
    "框", "案", "桉", "桌", "桎", "桐", "桑", "桓", "桔", "桠", "桡", "桢",
    "档", "桤", "桥", "桦", "桧", "桨", "桩", "桶", "桷", "梁", "梃", "梅",
    "梆", "梏", "梓", "梗", "梢", "梦", "梧", "梨", "梭", "梯", "械", "梳",
    "梵", "梽", "检", "棂", "棉", "棋", "棍", "棐", "棒", "棓", "棕", "棘",
    "棚", "棟", "棠", "棡", "棣", "棪", "森", "棰", "棱", "棵", "棹", "棺",
    "棽", "椀", "椁", "椅", "椋", "植", "椎", "椐", "椑", "椒", "椟", "椭",
    "椰", "椴", "椹", "椽", "椿", "楂", "楊", "楔", "楗", "楚", "楝", "楞",
    "楠", "楣", "楦", "楫", "楮", "楷", "楸", "楹", "楼", "榀", "概", "榃",
    "榄", "榅", "榆", "榇", "榈", "榉", "榍", "榔", "榕", "榛", "榜", "榧",
    "榨", "榫", "榭", "榮", "榱", "榴", "榷", "榻", "榼", "槁", "槃", "槊",
    "槌", "槎", "槐", "槑", "槓", "槚", "槛", "槟", "槺", "槽", "槿", "樊",
    "樑", "樓", "樗", "樘", "標", "樟", "模", "樨", "横", "樯", "樱", "樵",
    "樽", "樾", "橄", "橇", "橋", "橐", "橘", "橙", "橡", "橦", "橫", "橱",
    "橹", "檀", "檄", "檐", "檑", "檔", "檗", "檟", "檠", "檢", "檩", "檬",
    "櫃", "欠", "次", "欢", "欣", "欤", "欧", "欲", "欷", "欺", "欻", "款",
    "歆", "歇", "歉", "歌", "歔", "歘", "歙", "止", "正", "此", "步", "武",
    "歧", "歪", "歹", "死", "歼", "殁", "殂", "殃", "殄", "殆", "殇", "殉",
    "殊", "残", "殒", "殓", "殖", "殚", "殛", "殡", "殪", "殳", "殴", "段",
    "殷", "殽", "殿", "毁", "毂", "毅", "毋", "母", "每", "毒", "毓", "比",
    "毕", "毗", "毙", "毛", "毡", "毫", "毯", "毳", "氅", "氆", "氇", "氏",
    "氐", "民", "氓", "气", "氖", "氙", "氛", "氟", "氡", "氢", "氤", "氦",
    "氧", "氨", "氩", "氮", "氯", "氰", "氲", "水", "永", "氹", "氽", "氾",
    "氿", "汀", "汁", "求", "汇", "汈", "汉", "汊", "汎", "汐", "汔", "汕",
    "汗", "汛", "汜", "汝", "汞", "江", "池", "污", "汤", "汨", "汩", "汪",
    "汫", "汭", "汰", "汲", "汴", "汶", "汹", "汽", "汾", "沁", "沂", "沃",
    "沄", "沅", "沆", "沈", "沉", "沌", "沐", "沓", "沔", "沙", "沚", "沛",
    "沟", "没", "沣", "沥", "沦", "沧", "沨", "沩", "沪", "沫", "沬", "沭",
    "沮", "沱", "河", "沸", "油", "沺", "治", "沼", "沽", "沾", "沿", "泂",
    "泃", "泄", "泅", "泉", "泊", "泌", "泐", "泒", "泓", "泔", "法", "泖",
    "泗", "泛", "泞", "泠", "泡", "波", "泣", "泥", "注", "泪", "泫", "泮",
    "泯", "泰", "泱", "泳", "泵", "泷", "泸", "泺", "泻", "泼", "泽", "泾",
    "洁", "洄", "洇", "洈", "洋", "洌", "洎", "洑", "洒", "洗", "洙", "洛",
    "洞", "洟", "洢", "洣", "津", "洧", "洩", "洪", "洮", "洱", "洲", "洳",
    "洴", "洵", "洸", "洹", "洺", "活", "洼", "洽", "派", "流", "浃", "浅",
    "浆", "浇", "浈", "浉", "浊", "测", "浍", "济", "浏", "浐", "浑", "浒",
    "浓", "浔", "浙", "浚", "浛", "浜", "浞", "浠", "浡", "浣", "浥", "浦",
    "浩", "浪", "浬", "浮", "浯", "浰", "浴", "海", "浸", "浼", "涂", "涅",
    "消", "涉", "涌", "涎", "涓", "涔", "涕", "涛", "涝", "涞", "涟", "涠",
    "涡", "涣", "涤", "润", "涧", "涨", "涩", "涪", "涮", "涯", "液", "涴",
    "涵", "涸", "涿", "淀", "淄", "淅", "淆", "淇", "淋", "淌", "淏", "淑",
    "淖", "淘", "淙", "淝", "淞", "淠", "淡", "淤", "淦", "淩", "淫", "淬",
    "淮", "淯", "淰", "深", "淳", "混", "淹", "添", "淼", "清", "渊", "渌",
    "渍", "渎", "渐", "渑", "渔", "渖", "渗", "渚", "渝", "渟", "渠", "渡",
    "渣", "渤", "渥", "温", "測", "渭", "港", "渲", "渴", "游", "渺", "湃",
    "湄", "湉", "湍", "湎", "湑", "湓", "湔", "湖", "湘", "湛", "湜", "湟",
    "湦", "湧", "湫", "湮", "湲", "湴", "湾", "湿", "溁", "溃", "溅", "溆",
    "溇", "溉", "溍", "溏", "源", "溜", "溟", "溢", "溥", "溦", "溧", "溪",
    "溫", "溯", "溱", "溲", "溴", "溶", "溷", "溺", "滁", "滂", "滆", "滇",
    "滈", "滉", "滋", "滏", "滑", "滓", "滔", "滕", "滘", "滚", "滞", "滟",
    "滠", "满", "滢", "滤", "滥", "滦", "滧", "滨", "滩", "滴", "滹", "漂",
    "漆", "漈", "漉", "漍", "漏", "漓", "演", "漕", "漖", "漠", "漩", "漪",
    "漫", "漭", "漯", "漱", "漳", "漴", "漷", "漹", "漾", "潆", "潇", "潋",
    "潍", "潘", "潜", "潞", "潢", "潤", "潦", "潭", "潮", "潴", "潸", "潺",
    "潼", "澄", "澈", "澉", "澋", "澌", "澍", "澎", "澔", "澛", "澜", "澡",
    "澥", "澧", "澳", "澹", "激", "濂", "濉", "濑", "濒", "濛", "濞", "濠",
    "濡", "濬", "濮", "濯", "濰", "瀍", "瀑", "瀚", "瀛", "瀹", "瀼", "灈",
    "灌", "灏", "灜", "灞", "火", "灭", "灯", "灰", "灵", "灶", "灸", "灼",
    "灾", "灿", "炀", "炅", "炆", "炉", "炊", "炎", "炒", "炔", "炕", "炖",
    "炘", "炙", "炜", "炟", "炤", "炫", "炬", "炭", "炮", "炯", "炳", "炷",
    "炸", "点", "炼", "炽", "烁", "烂", "烃", "烈", "烊", "烔", "烘", "烙",
    "烛", "烜", "烝", "烟", "烤", "烦", "烧", "烨", "烩", "烫", "烬", "热",
    "烯", "烷", "烹", "烺", "烽", "焉", "焊", "焌", "焓", "焕", "焖", "焘",
    "焙", "焚", "焜", "焦", "焮", "焯", "焰", "焱", "然", "煅", "煇", "煊",
    "煌", "煎", "煕", "煖", "煚", "煜", "煞", "煤", "煦", "照", "煨", "煬",
    "煮", "煲", "煽", "熀", "熄", "熇", "熊", "熏", "熔", "熖", "熙", "熟",
    "熠", "熨", "熬", "熳", "熹", "燃", "燊", "燎", "燏", "燔", "燕", "燚",
    "燠", "燥", "燧", "燮", "燹", "燿", "爆", "爇", "爔", "爨", "爪", "爬",
    "爰", "爱", "爲", "爵", "父", "爷", "爸", "爹", "爻", "爽", "爿", "片",
    "版", "牌", "牍", "牒", "牖", "牙", "牛", "牝", "牟", "牡", "牢", "牤",
    "牦", "牧", "物", "牮", "牯", "牲", "牵", "特", "牺", "犀", "犁", "犄",
    "犇", "犊", "犋", "犍", "犒", "犟", "犬", "犯", "犴", "状", "犷", "犹",
    "狁", "狂", "狃", "狄", "狈", "狎", "狐", "狒", "狗", "狙", "狝", "狞",
    "狠", "狡", "狩", "独", "狭", "狮", "狰", "狱", "狲", "狸", "狻", "狼",
    "猃", "猇", "猊", "猎", "猕", "猖", "猗", "猛", "猜", "猝", "猢", "猥",
    "猩", "猪", "猫", "猬", "献", "猱", "猴", "猷", "猾", "猿", "獐", "獗",
    "獠", "獬", "獭", "獾", "玄", "率", "玉", "王", "玎", "玏", "玑", "玓",
    "玕", "玖", "玘", "玙", "玚", "玛", "玟", "玠", "玢", "玥", "玦", "玩",
    "玫", "玭", "玮", "环", "现", "玲", "玳", "玷", "玺", "玻", "珀", "珂",
    "珅", "珈", "珉", "珊", "珍", "珏", "珐", "珑", "珖", "珙", "珞", "珠",
    "珣", "珥", "珧", "珩", "珪", "班", "珮", "珰", "珲", "珵", "珺", "珽",
    "球", "琅", "理", "琇", "琉", "琊", "琍", "琎", "琏", "琐", "琓", "琖",
    "琚", "琛", "琢", "琤", "琥", "琦", "琨", "琪", "琬", "琭", "琮", "琯",
    "琰", "琳", "琴", "琵", "琶", "琼", "瑀", "瑁", "瑄", "瑆", "瑊", "瑒",
    "瑕", "瑗", "瑙", "瑚", "瑛", "瑜", "瑞", "瑟", "瑢", "瑧", "瑨", "瑩",
    "瑭", "瑰", "瑱", "瑶", "瑷", "瑸", "瑾", "璀", "璁", "璃", "璆", "璇",
    "璋", "璎", "璐", "璘", "璜", "璞", "璟", "璠", "璧", "璨", "璩", "環",
    "璿", "瓅", "瓒", "瓛", "瓜", "瓠", "瓢", "瓣", "瓦", "瓮", "瓯", "瓴",
    "瓶", "瓷", "瓻", "甄", "甌", "甍", "甑", "甘", "甙", "甚", "甜", "生",
    "甡", "産", "甥", "甦", "用", "甩", "甪", "甫", "甬", "甭", "甯", "田",
    "由", "甲", "申", "电", "男", "甸", "町", "画", "甽", "甾", "畀", "畅",
    "畇", "畈", "畋", "界", "畎", "畏", "畑", "畓", "畔", "留", "畚", "畛",
    "畜", "畤", "略", "畦", "番", "畯", "畲", "畴", "畸", "畹", "畿", "疃",
    "疆", "疋", "疏", "疑", "疗", "疙", "疚", "疝", "疟", "疡", "疣", "疤",
    "疥", "疫", "疮", "疯", "疱", "疲", "疴", "疵", "疸", "疹", "疼", "疽",
    "疾", "痂", "病", "症", "痈", "痉", "痊", "痍", "痒", "痔", "痕", "痘",
    "痛", "痞", "痢", "痣", "痤", "痧", "痪", "痫", "痰", "痴", "痹", "痼",
    "痿", "瘀", "瘁", "瘐", "瘗", "瘘", "瘙", "瘟", "瘠", "瘢", "瘤", "瘥",
    "瘦", "瘩", "瘪", "瘫", "瘳", "瘴", "瘵", "瘸", "瘾", "癀", "療", "癌",
    "癔", "癖", "癜", "癞", "癣", "癫", "癸", "登", "發", "白", "百", "癿",
    "皁", "皂", "的", "皆", "皇", "皈", "皊", "皋", "皎", "皑", "皓", "皖",
    "皙", "皛", "皝", "皞", "皤", "皮", "皱", "皴", "皿", "盂", "盅", "盆",
    "盈", "益", "盍", "盎", "盏", "盐", "监", "盒", "盔", "盖", "盗", "盘",
    "盛", "盟", "盥", "目", "盯", "盱", "盲", "直", "相", "盹", "盼", "盾",
    "省", "眇", "眈", "眉", "看", "眙", "眛", "真", "眠", "眢", "眦", "眨",
    "眩", "眭", "眯", "眶", "眷", "眸", "眺", "眼", "着", "睁", "睆", "睇",
    "睐", "睑", "睒", "睚", "睛", "睡", "睢", "督", "睦", "睨", "睪", "睫",
    "睬", "睹", "睽", "睾", "睿", "瞀", "瞄", "瞅", "瞋", "瞌", "瞎", "瞑",
    "瞒", "瞟", "瞠", "瞥", "瞧", "瞩", "瞪", "瞬", "瞭", "瞰", "瞳", "瞻",
    "瞽", "瞾", "瞿", "矗", "矛", "矜", "矢", "矣", "知", "矦", "矩", "矫",
    "短", "矮", "石", "矶", "矽", "矾", "矿", "砀", "码", "砂", "砌", "砍",
    "砒", "研", "砖", "砚", "砝", "砟", "砣", "砥", "砦", "砧", "砩", "砬",
    "砭", "砰", "砲", "破", "砵", "砷", "砸", "砺", "砻", "砼", "砾", "础",
    "硃", "硅", "硇", "硋", "硍", "硎", "硐", "硒", "硕", "硖", "硗", "硙",
    "硚", "硝", "硫", "硬", "确", "硷", "硼", "碁", "碇", "碉", "碌", "碍",
    "碎", "碑", "碓", "碗", "碘", "碚", "碛", "碟", "碡", "碣", "碧", "碰",
    "碱", "碲", "碳", "碴", "碶", "碾", "磁", "磅", "磉", "磊", "磋", "磐",
    "磑", "磔", "磕", "磘", "磙", "磛", "磜", "磡", "磨", "磬", "磴", "磷",
    "磹", "磺", "磻", "磾", "礁", "礐", "礤", "礴", "示", "礻", "礼", "礽",
    "社", "祀", "祁", "祃", "祇", "祈", "祉", "祎", "祐", "祓", "祖", "祗",
    "祚", "祛", "祜", "祝", "神", "祟", "祠", "祥", "祧", "票", "祭", "祯",
    "祷", "祸", "祺", "禀", "禁", "禄", "禅", "禇", "福", "禕", "禚", "禛",
    "禤", "禧", "禳", "禹", "禺", "离", "禽", "禾", "秀", "私", "秃", "秉",
    "秋", "种", "秏", "科", "秒", "秘", "租", "秣", "秤", "秦", "秧", "秩",
    "秭", "积", "称", "秸", "移", "秽", "秾", "稀", "稂", "程", "稍", "税",
    "稔", "稗", "稚", "稞", "稠", "稣", "稳", "稷", "稹", "稻", "稼", "稽",
    "稿", "穂", "穆", "穑", "穗", "穰", "穴", "究", "穷", "穹", "空", "穿",
    "突", "窃", "窄", "窈", "窊", "窍", "窑", "窒", "窕", "窖", "窗", "窘",
    "窜", "窝", "窟", "窠", "窣", "窥", "窦", "窨", "窬", "窭", "窿", "立",
    "竑", "竖", "站", "竜", "竞", "竟", "章", "竣", "童", "竦", "竫", "竭",
    "端", "競", "竹", "竺", "竻", "竽", "竿", "笃", "笄", "笆", "笈", "笋",
    "笏", "笑", "笔", "笕", "笙", "笛", "笞", "笠", "笤", "笥", "符", "笨",
    "笪", "笫", "第", "笮", "笳", "笺", "笼", "筀", "等", "筋", "筌", "筏",
    "筐", "筑", "筒", "答", "策", "筛", "筜", "筝", "筠", "筮", "筱", "筲",
    "筵", "筷", "筹", "筼", "签", "简", "箍", "箐", "箔", "箕", "算", "管",
    "箦", "箧", "箩", "箫", "箬", "箭", "箱", "箴", "箸", "篁", "篆", "篇",
    "篑", "篓", "篙", "篝", "篡", "篢", "篦", "篪", "篮", "篱", "篷", "篾",
    "簇", "簋", "簌", "簏", "簕", "簖", "簧", "簪", "簸", "簿", "籁", "籍",
    "米", "类", "籼", "籽", "粄", "粉", "粑", "粒", "粕", "粗", "粘", "粜",
    "粝", "粟", "粤", "粥", "粦", "粪", "粮", "粱", "粲", "粳", "粹", "粼",
    "粽", "精", "粿", "糁", "糅", "糊", "糌", "糍", "糕", "糖", "糗", "糙",
    "糜", "糟", "糠", "糯", "系", "紊", "素", "索", "紧", "紫", "紬", "累",
    "細", "組", "絜", "絮", "統", "絷", "綦", "線", "縂", "縠", "縢", "縯",
    "縻", "總", "繁", "繇", "纂", "纔", "纠", "纡", "红", "纣", "纤", "纥",
    "约", "级", "纨", "纪", "纫", "纬", "纭", "纮", "纯", "纰", "纱", "纲",
    "纳", "纵", "纶", "纷", "纸", "纹", "纺", "纻", "纽", "纾", "线", "绀",
    "绁", "练", "组", "绅", "细", "织", "终", "绊", "绌", "绍", "绎", "经",
    "绐", "绑", "绒", "结", "绔", "绕", "绖", "绘", "给", "绚", "绛", "络",
    "绝", "绞", "统", "绠", "绡", "绢", "绣", "绥", "绦", "继", "绨", "绩",
    "绪", "绫", "续", "绮", "绯", "绰", "绳", "维", "绵", "绶", "绷", "绸",
    "绺", "绻", "综", "绽", "绾", "绿", "缀", "缁", "缄", "缅", "缆", "缇",
    "缈", "缉", "缎", "缐", "缑", "缒", "缓", "缔", "缕", "编", "缗", "缘",
    "缙", "缚", "缜", "缝", "缞", "缟", "缠", "缢", "缤", "缥", "缦", "缧",
    "缨", "缩", "缪", "缫", "缭", "缮", "缯", "缰", "缱", "缳", "缴", "缵",
    "缶", "缸", "缺", "罂", "罄", "罅", "罐", "网", "罔", "罕", "罗", "罘",
    "罚", "罡", "罢", "罥", "罩", "罪", "置", "署", "罳", "罴", "罹", "罾",
    "羁", "羊", "羌", "美", "羑", "羔", "羖", "羚", "羞", "羟", "羡", "群",
    "義", "羯", "羲", "羸", "羹", "羽", "羿", "翀", "翁", "翃", "翅", "翊",
    "翌", "翎", "翔", "翕", "翘", "翚", "翛", "翟", "翠", "翡", "翥", "翦",
    "翩", "翮", "翯", "翰", "翱", "翳", "翻", "翼", "翾", "耀", "老", "考",
    "耄", "者", "耆", "耇", "耋", "而", "耍", "耎", "耐", "耑", "耒", "耕",
    "耗", "耘", "耙", "耜", "耦", "耨", "耩", "耳", "耶", "耸", "耻", "耽",
    "耿", "聂", "聃", "聆", "聊", "聋", "职", "聒", "联", "聖", "聘", "聚",
    "聩", "聪", "聯", "聲", "聿", "肃", "肄", "肆", "肇", "肉", "肋", "肌",
    "肓", "肖", "肘", "肚", "肛", "肜", "肝", "肠", "股", "肢", "肤", "肥",
    "肩", "肪", "肮", "肯", "肱", "育", "肴", "肸", "肺", "肽", "肾", "肿",
    "胀", "胁", "胃", "胄", "胆", "背", "胎", "胖", "胙", "胚", "胜", "胝",
    "胞", "胡", "胤", "胥", "胧", "胪", "胫", "胭", "胯", "胰", "胱", "胳",
    "胶", "胸", "胺", "能", "胾", "脁", "脂", "脆", "脉", "脊", "脍", "脏",
    "脐", "脑", "脓", "脔", "脖", "脚", "脯", "脱", "脲", "脸", "脾", "腆",
    "腈", "腉", "腊", "腋", "腌", "腐", "腑", "腓", "腔", "腕", "腥", "腩",
    "腭", "腮", "腰", "腱", "腴", "腹", "腺", "腻", "腼", "腾", "腿", "膀",
    "膈", "膊", "膏", "膑", "膘", "膛", "膜", "膝", "膦", "膨", "膳", "膺",
    "膻", "臀", "臂", "臃", "臆", "臊", "臛", "臣", "臧", "自", "臬", "臭",
    "至", "致", "臻", "臼", "臾", "舀", "舁", "舂", "舄", "舅", "舆", "舌",
    "舍", "舐", "舒", "舔", "舛", "舜", "舞", "舟", "舡", "舢", "舨", "航",
    "舫", "般", "舰", "舱", "舲", "舵", "舶", "舷", "舸", "船", "艇", "艘",
    "艚", "艞", "艮", "良", "艰", "色", "艳", "艺", "艻", "艽", "艾", "节",
    "芃", "芈", "芊", "芋", "芍", "芎", "芒", "芗", "芘", "芙", "芜", "芝",
    "芡", "芥", "芦", "芩", "芪", "芫", "芬", "芭", "芮", "芯", "芰", "花",
    "芳", "芶", "芷", "芸", "芹", "芽", "芾", "苁", "苄", "苇", "苈", "苋",
    "苌", "苍", "苎", "苏", "苑", "苒", "苓", "苔", "苕", "苗", "苛", "苜",
    "苞", "苟", "苠", "苡", "苣", "若", "苦", "苧", "苫", "苯", "英", "苳",
    "苴", "苷", "苹", "苻", "苾", "苿", "茀", "茁", "茂", "范", "茄", "茅",
    "茆", "茈", "茉", "茌", "茎", "茏", "茔", "茕", "茗", "茘", "茜", "茤",
    "茧", "茨", "茫", "茬", "茭", "茯", "茱", "茳", "茴", "茵", "茶", "茸",
    "茹", "茼", "荀", "荃", "荄", "荆", "荇", "草", "荏", "荐", "荒", "荔",
    "荘", "荚", "荜", "荞", "荟", "荠", "荡", "荣", "荤", "荥", "荦", "荧",
    "荩", "荪", "荫", "荭", "药", "荷", "荸", "荻", "荼", "荿", "莅", "莆",
    "莉", "莊", "莎", "莒", "莓", "莘", "莙", "莛", "莜", "莞", "莠", "莨",
    "莩", "莪", "莫", "莱", "莲", "莳", "莴", "获", "莹", "莺", "莼", "莽",
    "菀", "菁", "菂", "菅", "菇", "菉", "菊", "菌", "菏", "菑", "菓", "菖",
    "菘", "菜", "菟", "菠", "菡", "菥", "菩", "華", "菰", "菱", "菲", "菴",
    "菻", "菽", "萁", "萃", "萄", "萊", "萌", "萍", "萎", "萏", "萝", "萤",
    "营", "萦", "萧", "萨", "萩", "萬", "萱", "萸", "萼", "落", "葆", "葑",
    "著", "葛", "葡", "董", "葩", "葫", "葬", "葭", "葱", "葳", "葵", "葶",
    "葸", "葺", "蒂", "蒉", "蒋", "蒌", "蒗", "蒙", "蒜", "蒨", "蒯", "蒲",
    "蒴", "蒸", "蒺", "蒽", "蒿", "蓁", "蓄", "蓆", "蓉", "蓍", "蓐", "蓓",
    "蓖", "蓝", "蓟", "蓠", "蓢", "蓥", "蓦", "蓬", "蓼", "蓿", "蔈", "蔑",
    "蔓", "蔗", "蔚", "蔡", "蔫", "蔬", "蔷", "蔸", "蔺", "蔼", "蔽", "蕃",
    "蕉", "蕊", "蕗", "蕙", "蕤", "蕨", "蕰", "蕲", "蕴", "蕺", "蕻", "蕾",
    "薄", "薇", "薏", "薛", "薜", "薤", "薨", "薪", "薮", "薯", "薰", "薷",
    "藁", "藉", "藍", "藏", "藐", "藓", "藕", "藜", "藠", "藤", "藩", "藻",
    "藿", "蘅", "蘋", "蘑", "蘧", "蘭", "蘸", "虎", "虏", "虐", "虑", "虒",
    "虓", "虔", "虚", "虞", "號", "虢", "虫", "虬", "虮", "虱", "虹", "虺",
    "虽", "虾", "蚀", "蚁", "蚂", "蚊", "蚌", "蚓", "蚕", "蚝", "蚡", "蚣",
    "蚤", "蚧", "蚩", "蚬", "蚯", "蚰", "蚶", "蚺", "蛀", "蛆", "蛇", "蛊",
    "蛋", "蛎", "蛐", "蛔", "蛙", "蛛", "蛟", "蛤", "蛩", "蛭", "蛮", "蛰",
    "蛲", "蛳", "蛹", "蛾", "蜀", "蜂", "蜃", "蜇", "蜈", "蜊", "蜍", "蜒",
    "蜓", "蜕", "蜗", "蜘", "蜚", "蜜", "蜞", "蜡", "蜢", "蜥", "蜴", "蜷",
    "蜻", "蜿", "蝇", "蝉", "蝎", "蝗", "蝙", "蝠", "蝮", "蝴", "蝶", "蝼",
    "螂", "螃", "螅", "融", "螨", "螫", "螭", "螳", "螺", "蟆", "蟋", "蟒",
    "蟠", "蟥", "蟭", "蟹", "蟾", "蠕", "蠡", "蠢", "蠹", "血", "衅", "行",
    "衍", "衎", "衔", "衖", "街", "衙", "衡", "衢", "衣", "补", "表", "衩",
    "衫", "衬", "衮", "衰", "衲", "衷", "衽", "衾", "衿", "袁", "袂", "袄",
    "袅", "袆", "袈", "袋", "袍", "袒", "袖", "袜", "袤", "被", "袭", "袱",
    "袴", "裀", "裁", "裂", "装", "裆", "裔", "裕", "裘", "裙", "裝", "裟",
    "裡", "裢", "裤", "裨", "裰", "裱", "裳", "裴", "裸", "裹", "裾", "褂",
    "褊", "褐", "褒", "褓", "褔", "褚", "褛", "褡", "褥", "褪", "褫", "褴",
    "褶", "襁", "襄", "襆", "襟", "襦", "西", "要", "覃", "覆", "視", "见",
    "观", "规", "觅", "视", "觇", "览", "觉", "觊", "觌", "觎", "觐", "觑",
    "角", "觖", "觚", "觜", "觞", "解", "觥", "触", "觳", "言", "訇", "計",
    "訚", "設", "訸", "訾", "詈", "詠", "詹", "誉", "誌", "誓", "諸", "謦",
    "譞", "警", "譬", "讙", "计", "订", "讣", "认", "讥", "讦", "讧", "讨",
    "让", "讪", "讫", "训", "议", "讯", "记", "讲", "讳", "讴", "讵", "讶",
    "讷", "许", "讹", "论", "讼", "讽", "设", "访", "诀", "证", "诂", "诃",
    "评", "诅", "识", "诈", "诉", "诊", "诋", "词", "诎", "诏", "译", "诒",
    "试", "诗", "诘", "诙", "诚", "诛", "诜", "话", "诞", "诟", "诠", "诡",
    "询", "诣", "诤", "该", "详", "诧", "诨", "诩", "诫", "诬", "语", "诮",
    "误", "诰", "诱", "诲", "诳", "说", "诵", "请", "诸", "诺", "读", "诽",
    "课", "诿", "谀", "谁", "调", "谄", "谅", "谆", "谇", "谈", "谊", "谋",
    "谌", "谍", "谎", "谏", "谐", "谑", "谒", "谓", "谔", "谕", "谗", "谙",
    "谚", "谛", "谜", "谞", "谟", "谡", "谢", "谣", "谤", "谥", "谦", "谧",
    "谨", "谩", "谪", "谬", "谭", "谮", "谯", "谰", "谱", "谲", "谳", "谴",
    "谶", "谷", "谿", "豁", "豆", "豇", "豉", "豌", "豐", "豕", "豚", "象",
    "豢", "豨", "豪", "豫", "豭", "豳", "豸", "豹", "豺", "貂", "貉", "貌",
    "貔", "貟", "資", "贇", "贝", "贞", "负", "贠", "贡", "财", "责", "贤",
    "败", "账", "货", "质", "贩", "贪", "贫", "贬", "购", "贮", "贯", "贰",
    "贱", "贲", "贳", "贴", "贵", "贶", "贷", "贸", "费", "贺", "贻", "贼",
    "贽", "贾", "贿", "赀", "赁", "赂", "赃", "资", "赅", "赇", "赈", "赉",
    "赊", "赋", "赌", "赍", "赎", "赏", "赐", "赓", "赔", "赖", "赘", "赚",
    "赛", "赜", "赝", "赞", "赟", "赠", "赡", "赢", "赣", "赤", "赦", "赧",
    "赪", "赫", "赭", "走", "赳", "赴", "赵", "赶", "起", "趁", "趄", "超",
    "越", "趋", "趟", "趣", "趱", "足", "趴", "趵", "趸", "趹", "趺", "趾",
    "跂", "跃", "跄", "跆", "跋", "跌", "跑", "跖", "跚", "跛", "距", "跞",
    "跟", "跣", "跤", "跨", "跪", "跬", "路", "跳", "践", "跷", "跸", "跹",
    "跺", "跻", "跽", "踅", "踉", "踊", "踌", "踏", "踔", "踝", "踞", "踟",
    "踢", "踣", "踧", "踩", "踪", "踯", "踰", "踱", "踵", "踹", "踽", "蹀",
    "蹂", "蹄", "蹇", "蹈", "蹉", "蹊", "蹋", "蹑", "蹒", "蹙", "蹦", "蹩",
    "蹬", "蹭", "蹰", "蹲", "蹴", "蹶", "蹻", "蹿", "躁", "躅", "躇", "躏",
    "躞", "身", "躬", "躯", "躲", "躺", "車", "軍", "輋", "车", "轧", "轨",
    "轩", "轫", "转", "轭", "轮", "软", "轰", "轲", "轳", "轴", "轵", "轶",
    "轸", "轺", "轻", "轼", "载", "轾", "轿", "辂", "较", "辄", "辅", "辆",
    "辇", "辈", "辉", "辊", "辋", "辍", "辎", "辐", "辑", "输", "辔", "辕",
    "辖", "辗", "辘", "辙", "辛", "辜", "辞", "辟", "辣", "辨", "辩", "辫",
    "辰", "辱", "辶", "边", "辽", "达", "迁", "迂", "迄", "迅", "过", "迈",
    "迎", "运", "近", "迓", "返", "迕", "还", "这", "进", "远", "违", "连",
    "迟", "迢", "迤", "迥", "迦", "迨", "迩", "迪", "迫", "迭", "迮", "述",
    "迳", "迴", "迷", "迸", "迹", "迺", "追", "退", "送", "适", "逃", "逄",
    "逅", "逆", "选", "逊", "逋", "逍", "透", "逐", "逑", "递", "途", "逖",
    "逗", "通", "逛", "逝", "逞", "速", "造", "逡", "逢", "逦", "逮", "逯",
    "逵", "逶", "逸", "逻", "逼", "逾", "遁", "遂", "遄", "遆", "遇", "遊",
    "遍", "遏", "遐", "遑", "遒", "道", "遗", "遘", "遛", "遢", "遣", "遥",
    "遨", "遫", "遭", "遮", "遴", "遵", "遶", "遹", "遽", "避", "邀", "邂",
    "邃", "邈", "邋", "邑", "邓", "邕", "邗", "邙", "邛", "邝", "邠", "邡",
    "邢", "那", "邦", "邨", "邪", "邬", "邮", "邯", "邰", "邱", "邳", "邴",
    "邵", "邸", "邹", "邺", "邻", "邾", "郁", "郄", "郅", "郇", "郊", "郎",
    "郏", "郐", "郑", "郓", "郗", "郚", "郜", "郝", "郞", "郡", "郢", "郤",
    "郦", "郧", "部", "郪", "郫", "郭", "郯", "郴", "郸", "都", "郾", "郿",
    "鄂", "鄄", "鄌", "鄙", "鄚", "鄜", "鄞", "鄠", "鄢", "鄣", "鄯", "鄱",
    "酂", "酃", "酄", "酆", "酇", "酉", "酊", "酋", "酌", "配", "酎", "酒",
    "酗", "酚", "酝", "酞", "酡", "酢", "酣", "酤", "酥", "酩", "酪", "酬",
    "酮", "酯", "酰", "酱", "酵", "酶", "酷", "酸", "酹", "酿", "醇", "醉",
    "醋", "醍", "醐", "醒", "醚", "醛", "醪", "醮", "醴", "醵", "醺", "釂",
    "采", "釉", "释", "里", "重", "野", "量", "釐", "金", "釜", "鈇", "鈜",
    "鈺", "鉏", "鉥", "鉴", "鉿", "銀", "銘", "銮", "鋆", "錡", "録", "錾",
    "鎏", "鎔", "鎮", "鏊", "鏐", "鏖", "鐘", "鐾", "鑑", "鑙", "鑫", "钇",
    "针", "钉", "钊", "钎", "钏", "钐", "钒", "钓", "钕", "钖", "钗", "钘",
    "钙", "钚", "钛", "钜", "钝", "钞", "钟", "钠", "钡", "钢", "钣", "钤",
    "钥", "钦", "钧", "钨", "钩", "钫", "钬", "钭", "钮", "钯", "钰", "钱",
    "钲", "钳", "钴", "钵", "钶", "钹", "钺", "钻", "钼", "钾", "钿", "铀",
    "铁", "铂", "铃", "铄", "铅", "铆", "铈", "铉", "铋", "铌", "铎", "铐",
    "铕", "铖", "铙", "铚", "铛", "铜", "铝", "铞", "铟", "铠", "铢", "铣",
    "铤", "铧", "铨", "铩", "铫", "铬", "铭", "铮", "铱", "铲", "铳", "铵",
    "银", "铷", "铸", "铺", "铼", "链", "铿", "销", "锁", "锂", "锃", "锄",
    "锅", "锆", "锈", "锉", "锋", "锌", "锎", "锏", "锐", "锑", "锒", "锖",
    "锗", "锘", "错", "锚", "锜", "锞", "锟", "锠", "锡", "锢", "锣", "锤",
    "锥", "锦", "锨", "锫", "锬", "锭", "键", "锯", "锰", "锱", "锲", "锴",
    "锵", "锶", "锷", "锹", "锺", "锻", "锽", "锾", "镀", "镁", "镂", "镇",
    "镈", "镉", "镊", "镌", "镍", "镐", "镑", "镒", "镓", "镔", "镕", "镖",
    "镗", "镘", "镛", "镜", "镝", "镞", "镠", "镡", "镣", "镤", "镧", "镨",
    "镪", "镫", "镬", "镭", "镯", "镰", "镱", "镳", "镵", "镶", "长", "開",
    "閒", "間", "閤", "闇", "闟", "门", "闩", "闪", "闫", "闭", "问", "闯",
    "闰", "闱", "闲", "闳", "间", "闵", "闷", "闸", "闹", "闺", "闻", "闼",
    "闽", "闾", "阀", "阁", "阂", "阃", "阅", "阆", "阈", "阉", "阊", "阍",
    "阎", "阏", "阐", "阑", "阔", "阕", "阖", "阗", "阙", "阚", "阜", "队",
    "阡", "阪", "阮", "阱", "防", "阳", "阴", "阵", "阶", "阻", "阾", "阿",
    "陀", "陂", "附", "际", "陆", "陇", "陈", "陉", "陋", "陌", "降", "限",
    "陔", "陕", "陛", "陞", "陟", "陡", "院", "除", "陨", "险", "陪", "陬",
    "陲", "陵", "陶", "陷", "隅", "隆", "隈", "隋", "隍", "随", "隐", "隔",
    "隗", "隘", "隙", "際", "障", "隧", "隰", "隳", "隶", "隹", "隼", "隽",
    "难", "雀", "雁", "雄", "雅", "集", "雇", "雉", "雌", "雍", "雎", "雏",
    "雒", "雕", "雨", "雩", "雪", "雯", "雲", "雳", "零", "雷", "雹", "電",
    "雾", "需", "霁", "霂", "霄", "霆", "震", "霈", "霉", "霍", "霎", "霏",
    "霓", "霖", "霜", "霞", "霣", "霭", "霰", "露", "霸", "霹", "霾", "青",
    "靓", "靖", "静", "靛", "非", "靠", "靡", "面", "靥", "革", "靳", "靴",
    "靶", "鞅", "鞋", "鞍", "鞑", "鞘", "鞚", "鞠", "鞣", "鞫", "鞭", "韂",
    "韓", "韡", "韦", "韧", "韩", "韪", "韫", "韬", "韭", "音", "韵", "韶",
    "韻", "頔", "頫", "頲", "顏", "顒", "页", "顶", "顷", "项", "顺", "须",
    "顼", "顽", "顾", "顿", "颀", "颁", "颂", "预", "颅", "领", "颇", "颈",
    "颉", "颊", "颋", "颌", "颍", "颐", "频", "颓", "颔", "颖", "颗", "题",
    "颚", "颛", "颜", "额", "颠", "颡", "颢", "颤", "颦", "颧", "风", "飏",
    "飒", "飓", "飔", "飕", "飘", "飙", "飚", "飞", "食", "飧", "飨", "餍",
    "餐", "餮", "饕", "饥", "饦", "饪", "饬", "饭", "饮", "饯", "饰", "饱",
    "饲", "饴", "饵", "饶", "饷", "饺", "饼", "饽", "饿", "馀", "馁", "馅",
    "馆", "馈", "馋", "馍", "馎", "馏", "馐", "馒", "馓", "馔", "馕", "首",
    "馗", "香", "馥", "馨", "驩", "马", "驭", "驮", "驯", "驰", "驱", "驳",
    "驴", "驶", "驷", "驸", "驹", "驺", "驻", "驼", "驽", "驾", "驿", "骀",
    "骁", "骂", "骄", "骅", "骆", "骇", "骈", "骉", "骊", "骋", "验", "骍",
    "骎", "骏", "骐", "骑", "骕", "骖", "骗", "骘", "骙", "骚", "骛", "骜",
    "骝", "骞", "骠", "骡", "骢", "骤", "骥", "骧", "骨", "骰", "骶", "骷",
    "骸", "骼", "髀", "髃", "髅", "髋", "髑", "髓", "髕", "高", "髡", "髦",
    "髫", "髭", "髯", "髻", "鬃", "鬓", "鬟", "鬣", "鬲", "鬻", "鬼", "魁",
    "魂", "魄", "魅", "魇", "魉", "魍", "魏", "魑", "魔", "鮀", "鱼", "鱿",
    "鲁", "鲅", "鲇", "鲈", "鲋", "鲍", "鲐", "鲑", "鲔", "鲖", "鲛", "鲜",
    "鲟", "鲠", "鲡", "鲤", "鲧", "鲨", "鲰", "鲲", "鲸", "鳃", "鳄", "鳊",
    "鳌", "鳍", "鳏", "鳖", "鳗", "鳜", "鳝", "鳞", "鴻", "鵾", "鶴", "鸟",
    "鸠", "鸡", "鸢", "鸣", "鸥", "鸦", "鸨", "鸩", "鸪", "鸫", "鸬", "鸭",
    "鸮", "鸯", "鸱", "鸳", "鸵", "鸶", "鸷", "鸹", "鸽", "鸾", "鸿", "鹁",
    "鹂", "鹃", "鹄", "鹅", "鹆", "鹉", "鹊", "鹌", "鹍", "鹏", "鹑", "鹗",
    "鹘", "鹚", "鹜", "鹞", "鹣", "鹤", "鹦", "鹧", "鹫", "鹭", "鹰", "鹳",
    "鹿", "麂", "麋", "麒", "麓", "麗", "麝", "麟", "麦", "麻", "麽", "麾",
    "黄", "黉", "黍", "黎", "黏", "黑", "黔", "默", "黛", "黜", "黝", "黟",
    "黠", "黯", "黾", "鼋", "鼍", "鼎", "鼐", "鼓", "鼠", "鼻", "鼾", "齐",
    "齿", "龁", "龄", "龈", "龊", "龋", "龌", "龍", "龑", "龙", "龚", "龛",
    "龟", "",  "︰", "﹐", "﹑", "﹒", "﹔", "﹖", "﹟", "＃", "（", "）",
    "＋", "，", "－", "．", "／", "０", "１", "２", "４", "５", "６", "７",
    "９", "：", "Ｂ", "～", "￥"};