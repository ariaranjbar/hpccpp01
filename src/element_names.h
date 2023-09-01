#ifndef ELEMENT_NAMES_H
#define ELEMENT_NAMES_H

#include <map>
#include <string>

namespace element_names {
constexpr unsigned char NOT_AN_ELEMENT = 0;
constexpr unsigned char H = 1;    // Hydrogen
constexpr unsigned char He = 2;   // Helium
constexpr unsigned char Li = 3;   // Lithium
constexpr unsigned char Be = 4;   // Beryllium
constexpr unsigned char B = 5;    // Boron
constexpr unsigned char C = 6;    // Carbon
constexpr unsigned char N = 7;    // Nitrogen
constexpr unsigned char O = 8;    // Oxygen
constexpr unsigned char F = 9;    // Fluorine
constexpr unsigned char Ne = 10;  // Neon
constexpr unsigned char Na = 11;  // Sodium
constexpr unsigned char Mg = 12;  // Magnesium
constexpr unsigned char Al = 13;  // Aluminum
constexpr unsigned char Si = 14;  // Silicon
constexpr unsigned char P = 15;   // Phosphorus
constexpr unsigned char S = 16;   // Sulfur
constexpr unsigned char Cl = 17;  // Chlorine
constexpr unsigned char Ar = 18;  // Argon
constexpr unsigned char K = 19;   // Potassium
constexpr unsigned char Ca = 20;  // Calcium
constexpr unsigned char Sc = 21;  // Scandium
constexpr unsigned char Ti = 22;  // Titanium
constexpr unsigned char V = 23;   // Vanadium
constexpr unsigned char Cr = 24;  // Chromium
constexpr unsigned char Mn = 25;  // Manganese
constexpr unsigned char Fe = 26;  // Iron
constexpr unsigned char Co = 27;  // Cobalt
constexpr unsigned char Ni = 28;  // Nickel
constexpr unsigned char Cu = 29;  // Copper
constexpr unsigned char Zn = 30;  // Zinc
constexpr unsigned char Ga = 31;  // Gallium
constexpr unsigned char Ge = 32;  // Germanium
constexpr unsigned char As = 33;  // Arsenic
constexpr unsigned char Se = 34;  // Selenium
constexpr unsigned char Br = 35;  // Bromine
constexpr unsigned char Kr = 36;  // Krypton
constexpr unsigned char Rb = 37;  // Rubidium
constexpr unsigned char Sr = 38;  // Strontium
constexpr unsigned char Y = 39;   // Yttrium
constexpr unsigned char Zr = 40;  // Zirconium
constexpr unsigned char Nb = 41;  // Niobium
constexpr unsigned char Mo = 42;  // Molybdenum
constexpr unsigned char Tc = 43;  // Technetium
constexpr unsigned char Ru = 44;  // Ruthenium
constexpr unsigned char Rh = 45;  // Rhodium
constexpr unsigned char Pd = 46;  // Palladium
constexpr unsigned char Ag = 47;  // Silver
constexpr unsigned char Cd = 48;  // Cadmium
constexpr unsigned char In = 49;  // Indium
constexpr unsigned char Sn = 50;  // Tin
constexpr unsigned char Sb = 51;  // Antimony
constexpr unsigned char Te = 52;  // Tellurium
constexpr unsigned char I = 53;   // Iodine
constexpr unsigned char Xe = 54;  // Xenon
constexpr unsigned char Cs = 55;  // Cesium
constexpr unsigned char Ba = 56;  // Barium
constexpr unsigned char La = 57;  // Lanthanum
constexpr unsigned char Ce = 58;  // Cerium
constexpr unsigned char Pr = 59;  // Praseodymium
constexpr unsigned char Nd = 60;  // Neodymium
constexpr unsigned char Pm = 61;  // Promethium
constexpr unsigned char Sm = 62;  // Samarium
constexpr unsigned char Eu = 63;  // Europium
constexpr unsigned char Gd = 64;  // Gadolinium
constexpr unsigned char Tb = 65;  // Terbium
constexpr unsigned char Dy = 66;  // Dysprosium
constexpr unsigned char Ho = 67;  // Holmium
constexpr unsigned char Er = 68;  // Erbium
constexpr unsigned char Tm = 69;  // Thulium
constexpr unsigned char Yb = 70;  // Ytterbium
constexpr unsigned char Lu = 71;  // Lutetium
constexpr unsigned char Hf = 72;  // Hafnium
constexpr unsigned char Ta = 73;  // Tantalum
constexpr unsigned char W = 74;   // Tungsten
constexpr unsigned char Re = 75;  // Rhenium
constexpr unsigned char Os = 76;  // Osmium
constexpr unsigned char Ir = 77;  // Iridium
constexpr unsigned char Pt = 78;  // Platinum
constexpr unsigned char Au = 79;  // Gold
constexpr unsigned char Hg = 80;  // Mercury
constexpr unsigned char Tl = 81;  // Thallium
constexpr unsigned char Pb = 82;  // Lead
constexpr unsigned char Bi = 83;  // Bismuth
constexpr unsigned char Po = 84;  // Polonium
constexpr unsigned char At = 85;  // Astatine
constexpr unsigned char Rn = 86;  // Radon
constexpr unsigned char Fr = 87;  // Francium
constexpr unsigned char Ra = 88;  // Radium
constexpr unsigned char Ac = 89;  // Actinium
constexpr unsigned char Th = 90;  // Thorium
constexpr unsigned char Pa = 91;  // Protactinium
constexpr unsigned char U = 92;   // Uranium
constexpr unsigned char Np = 93;  // Neptunium
constexpr unsigned char Pu = 94;  // Plutonium
constexpr unsigned char Am = 95;  // Americium
constexpr unsigned char Cm = 96;  // Curium
constexpr unsigned char Bk = 97;  // Berkelium
constexpr unsigned char Cf = 98;  // Californium
constexpr unsigned char Es = 99;  // Einsteinium
constexpr unsigned char Fm = 100; // Fermium
constexpr unsigned char Md = 101; // Mendelevium
constexpr unsigned char No = 102; // Nobelium
constexpr unsigned char Lr = 103; // Lawrencium
constexpr unsigned char Rf = 104; // Rutherfordium
constexpr unsigned char Db = 105; // Dubnium
constexpr unsigned char Sg = 106; // Seaborgium
constexpr unsigned char Bh = 107; // Bohrium
constexpr unsigned char Hs = 108; // Hassium
constexpr unsigned char Mt = 109; // Meitnerium
constexpr unsigned char Ds = 110; // Darmstadtium
constexpr unsigned char Rg = 111; // Roentgenium
constexpr unsigned char Cn = 112; // Copernicium
constexpr unsigned char Nh = 113; // Nihonium
constexpr unsigned char Fl = 114; // Flerovium
constexpr unsigned char Mc = 115; // Moscovium
constexpr unsigned char Lv = 116; // Livermorium
constexpr unsigned char Ts = 117; // Tennessine
constexpr unsigned char Og = 118; // Oganesson

const std::string ELEMENT_NAME[]{"NOT_AN_ELEMENT",
                                 "H",
                                 "He",
                                 "Li",
                                 "Be",
                                 "B",
                                 "C",
                                 "N",
                                 "O",
                                 "F",
                                 "Ne",
                                 "Na",
                                 "Mg",
                                 "Al",
                                 "Si",
                                 "P",
                                 "S",
                                 "Cl",
                                 "Ar",
                                 "K",
                                 "Ca",
                                 "Sc",
                                 "Ti",
                                 "V",
                                 "Cr",
                                 "Mn",
                                 "Fe",
                                 "Co",
                                 "Ni",
                                 "Cu",
                                 "Zn",
                                 "Ga",
                                 "Ge",
                                 "As",
                                 "Se",
                                 "Br",
                                 "Kr",
                                 "Rb",
                                 "Sr",
                                 "Y",
                                 "Zr",
                                 "Nb",
                                 "Mo",
                                 "Tc",
                                 "Ru",
                                 "Rh",
                                 "Pd",
                                 "Ag",
                                 "Cd",
                                 "In",
                                 "Sn",
                                 "Sb",
                                 "Te",
                                 "I",
                                 "Xe",
                                 "Cs",
                                 "Ba",
                                 "La",
                                 "Ce",
                                 "Pr",
                                 "Nd",
                                 "Pm",
                                 "Sm",
                                 "Eu",
                                 "Gd",
                                 "Tb",
                                 "Dy",
                                 "Ho",
                                 "Er",
                                 "Tm",
                                 "Yb",
                                 "Lu",
                                 "Hf",
                                 "Ta",
                                 "W",
                                 "Re",
                                 "Os",
                                 "Ir",
                                 "Pt",
                                 "Au",
                                 "Hg",
                                 "Tl",
                                 "Pb",
                                 "Bi",
                                 "Po",
                                 "At",
                                 "Rn",
                                 "Fr",
                                 "Ra",
                                 "Ac",
                                 "Th",
                                 "Pa",
                                 "U",
                                 "Np",
                                 "Pu",
                                 "Am",
                                 "Cm",
                                 "Bk",
                                 "Cf",
                                 "Es",
                                 "Fm",
                                 "Md",
                                 "No",
                                 "Lr",
                                 "Rf",
                                 "Db",
                                 "Sg",
                                 "Bh",
                                 "Hs",
                                 "Mt",
                                 "Ds",
                                 "Rg",
                                 "Cn",
                                 "Nh",
                                 "Fl",
                                 "Mc",
                                 "Lv",
                                 "Ts",
                                 "Og"};

const std::map<std::string, uint8_t> ELEMENT_NUMBER{
    {"NOT_AN_ELEMENT", NOT_AN_ELEMENT},
    {"H", H},
    {"He", He},
    {"Li", Li},
    {"Be", Be},
    {"B", B},
    {"C", C},
    {"N", N},
    {"O", O},
    {"F", F},
    {"Ne", Ne},
    {"Na", Na},
    {"Mg", Mg},
    {"Al", Al},
    {"Si", Si},
    {"P", P},
    {"S", S},
    {"Cl", Cl},
    {"Ar", Ar},
    {"K", K},
    {"Ca", Ca},
    {"Sc", Sc},
    {"Ti", Ti},
    {"V", V},
    {"Cr", Cr},
    {"Mn", Mn},
    {"Fe", Fe},
    {"Co", Co},
    {"Ni", Ni},
    {"Cu", Cu},
    {"Zn", Zn},
    {"Ga", Ga},
    {"Ge", Ge},
    {"As", As},
    {"Se", Se},
    {"Br", Br},
    {"Kr", Kr},
    {"Rb", Rb},
    {"Sr", Sr},
    {"Y", Y},
    {"Zr", Zr},
    {"Nb", Nb},
    {"Mo", Mo},
    {"Tc", Tc},
    {"Ru", Ru},
    {"Rh", Rh},
    {"Pd", Pd},
    {"Ag", Ag},
    {"Cd", Cd},
    {"In", In},
    {"Sn", Sn},
    {"Sb", Sb},
    {"Te", Te},
    {"I", I},
    {"Xe", Xe},
    {"Cs", Cs},
    {"Ba", Ba},
    {"La", La},
    {"Ce", Ce},
    {"Pr", Pr},
    {"Nd", Nd},
    {"Pm", Pm},
    {"Sm", Sm},
    {"Eu", Eu},
    {"Gd", Gd},
    {"Tb", Tb},
    {"Dy", Dy},
    {"Ho", Ho},
    {"Er", Er},
    {"Tm", Tm},
    {"Yb", Yb},
    {"Lu", Lu},
    {"Hf", Hf},
    {"Ta", Ta},
    {"W", W},
    {"Re", Re},
    {"Os", Os},
    {"Ir", Ir},
    {"Pt", Pt},
    {"Au", Au},
    {"Hg", Hg},
    {"Tl", Tl},
    {"Pb", Pb},
    {"Bi", Bi},
    {"Po", Po},
    {"At", At},
    {"Rn", Rn},
    {"Fr", Fr},
    {"Ra", Ra},
    {"Ac", Ac},
    {"Th", Th},
    {"Pa", Pa},
    {"U", U},
    {"Np", Np},
    {"Pu", Pu},
    {"Am", Am},
    {"Cm", Cm},
    {"Bk", Bk},
    {"Cf", Cf},
    {"Es", Es},
    {"Fm", Fm},
    {"Md", Md},
    {"No", No},
    {"Lr", Lr},
    {"Rf", Rf},
    {"Db", Db},
    {"Sg", Sg},
    {"Bh", Bh},
    {"Hs", Hs},
    {"Mt", Mt},
    {"Ds", Ds},
    {"Rg", Rg},
    {"Cn", Cn},
    {"Nh", Nh},
    {"Fl", Fl},
    {"Mc", Mc},
    {"Lv", Lv},
    {"Ts", Ts},
    {"Og", Og}};

const double ELEMENT_MASS[]{
    1.0,      1.00797,  4.00260,   6.941,    9.01218,  10.81,    12.011,
    14.0067,  15.9994,  18.998403, 20.179,   22.98977, 24.305,   26.98154,
    28.0855,  30.97376, 32.06,     35.453,   39.948,   39.0983,  40.08,
    44.9559,  47.90,    50.9415,   51.996,   54.9380,  55.847,   58.9332,
    58.70,    63.546,   65.38,     69.72,    72.59,    74.9216,  78.96,
    79.904,   83.80,    85.4678,   87.62,    88.9059,  91.22,    92.9064,
    95.94,    98.0,     101.07,    102.9055, 106.4,    107.868,  112.41,
    114.82,   118.69,   121.75,    127.60,   126.9045, 131.30,   132.9054,
    137.33,   138.9055, 140.12,    140.9077, 144.24,   145.0,    150.4,
    151.96,   157.25,   158.9254,  162.50,   164.9304, 167.26,   168.9342,
    173.04,   174.967,  178.49,    180.9479, 183.85,   186.207,  190.2,
    192.22,   195.09,   196.9665,  200.59,   204.37,   207.2,    208.9804,
    209.0,    210.0,    222.0,     223.0,    226.0254, 227.0278, 232.0381,
    231.0359, 238.029,  237.0482,  242.0,    243.0,    247.0,    247.0,
    251.0,    252.0,    257.0,     258.0,    250.0,    260.0,    261.0,
    262.0,    263.0,    262.0,     255.0,    256.0,    269.0,    272.0,
    272.0,    272.0,    272.0,     272.0,    272.0,    272.0,    272.0};

} // namespace element_names
#endif // __ELEMENT_NAMES_H