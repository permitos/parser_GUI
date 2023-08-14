#include "encodingtype.h"

map<int, char> EncodingType::createCP866() {

    map<int, char> CP866;

    CP866[128] = 'А';   CP866[143] = 'П';   CP866[158] = 'Ю';   CP866[173] = 'н';    CP866[233] = 'щ';   CP866[132] = 'Д';
    CP866[129] = 'Б';   CP866[144] = 'Р';   CP866[159] = 'Я';   CP866[174] = 'о';    CP866[234] = 'ъ';   CP866[133] = 'Е';
    CP866[130] = 'В';   CP866[145] = 'С';   CP866[160] = 'а';   CP866[175] = 'п';    CP866[235] = 'ы';   CP866[134] = 'Ж';
    CP866[131] = 'Г';   CP866[146] = 'Т';   CP866[161] = 'б';   CP866[224] = 'р';    CP866[236] = 'ь';   CP866[147] = 'У';
    CP866[135] = 'З';   CP866[150] = 'Ц';   CP866[165] = 'е';   CP866[225] = 'с';    CP866[237] = 'э';   CP866[148] = 'Ф';
    CP866[136] = 'И';   CP866[151] = 'Ч';   CP866[166] = 'ж';   CP866[226] = 'т';    CP866[238] = 'ю';   CP866[149] = 'Х';
    CP866[137] = 'Й';   CP866[152] = 'Ш';   CP866[167] = 'з';   CP866[227] = 'у';    CP866[239] = 'я';
    CP866[138] = 'К';   CP866[153] = 'Щ';   CP866[168] = 'и';   CP866[228] = 'ф';    CP866[240] = 'Ё';
    CP866[139] = 'Л';   CP866[154] = 'Ъ';   CP866[169] = 'й';   CP866[229] = 'х';    CP866[241] = 'ё';
    CP866[140] = 'М';   CP866[155] = 'Ы';   CP866[170] = 'к';   CP866[230] = 'ц';    CP866[162] = 'в';
    CP866[141] = 'Н';   CP866[156] = 'Ь';   CP866[171] = 'л';   CP866[231] = 'ч';    CP866[163] = 'г';
    CP866[142] = 'О';   CP866[157] = 'Э';   CP866[172] = 'м';   CP866[232] = 'ш';    CP866[164] = 'д';

    return CP866;
}

map<int, char> EncodingType::createKOI8() {

    map<int, char> KOI8;

    KOI8[163] = 'ё';   KOI8[203] = 'к';   KOI8[215] = 'в';   KOI8[227] = 'Ц';   KOI8[239] = 'О';   KOI8[251] = 'Ш';
    KOI8[192] = 'ю';   KOI8[204] = 'л';   KOI8[216] = 'ь';   KOI8[228] = 'Д';   KOI8[240] = 'П';   KOI8[252] = 'Э';
    KOI8[193] = 'а';   KOI8[205] = 'м';   KOI8[217] = 'ы';   KOI8[229] = 'Е';   KOI8[241] = 'Я';   KOI8[253] = 'Щ';
    KOI8[194] = 'б';   KOI8[206] = 'н';   KOI8[218] = 'з';   KOI8[230] = 'Ф';   KOI8[242] = 'Р';   KOI8[254] = 'Ч';
    KOI8[195] = 'ц';   KOI8[207] = 'о';   KOI8[219] = 'ш';   KOI8[231] = 'Г';   KOI8[243] = 'С';   KOI8[255] = 'Ъ';
    KOI8[196] = 'д';   KOI8[208] = 'п';   KOI8[220] = 'э';   KOI8[232] = 'Х';   KOI8[244] = 'Т';   KOI8[179] = 'Ё';
    KOI8[197] = 'е';   KOI8[209] = 'я';   KOI8[221] = 'щ';   KOI8[233] = 'И';   KOI8[245] = 'У';
    KOI8[198] = 'ф';   KOI8[210] = 'р';   KOI8[222] = 'ч';   KOI8[234] = 'Й';   KOI8[246] = 'Ж';
    KOI8[199] = 'г';   KOI8[211] = 'с';   KOI8[223] = 'ъ';   KOI8[235] = 'К';   KOI8[247] = 'В';
    KOI8[200] = 'х';   KOI8[212] = 'т';   KOI8[224] = 'Ю';   KOI8[236] = 'Л';   KOI8[248] = 'Ь';
    KOI8[201] = 'и';   KOI8[213] = 'у';   KOI8[225] = 'А';   KOI8[237] = 'М';   KOI8[249] = 'Ы';
    KOI8[202] = 'й';   KOI8[214] = 'ж';   KOI8[226] = 'Б';   KOI8[238] = 'Н';   KOI8[250] = 'З';

    return KOI8;
}

const map<int, char> EncodingType::_CP866 = EncodingType::createCP866();
const map<int, char> EncodingType::_KOI8 = EncodingType::createKOI8();

char EncodingType::getSymbolFromCP866(int numCoding) {

    if(_CP866.find(numCoding) != _CP866.end())
        return _CP866.at(numCoding);

    return (char) numCoding;
}

char EncodingType::getSymbolFromKOI8(int numCoding) {

    if(_KOI8.find(numCoding) != _KOI8.end())
        return _KOI8.at(numCoding);

    return (char) numCoding;
}
