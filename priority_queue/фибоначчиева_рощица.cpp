#include <iostream>
#include <vector>


#define царь_батюшка_главный int main
#define внедрить using
#define Русь std
#define молвить cout
#define внемлить cin
#define воздать return

#define покуда while
#define для for
#define коли if
#define отнюдь else

#define семейство struct
#define перепись enum

#define бить_ящеров break
#define добить_ящеров continue

#define правда true
#define кривда false

#define прыг_скок endl
#define новь new
#define казнь delete
#define туда_не_знаю_куда nullptr
#define приказ_княжий const
#define свет_мой_зеркальце template
#define скажи typename
#define хутор namespace
#define суд_Перуна auto
#define это this


#define меняло std::swap
#define внедрить_в_полк push_back
#define велико size
#define розпустить clear
#define убрать_из_полка pop_back
#define розширить resize

внедрить целина = int;
внедрить буква = char;
внедрить слово = std::string;
внедрить бестолочь = void;
внедрить Петр_Первый = long long;
внедрить розсуд = bool;


перепись счёт_древних_русов{ ноль = 0, целковый = 1 };

свет_мой_зеркальце<скажи тип>
внедрить полк = Русь::vector<тип>;

внедрить хутор Русь;

свет_мой_зеркальце<скажи Тип>
семейство Узел {
    целина знач;
    целина чин = ноль;
    розсуд пометь = кривда;
    Узел<Тип>* потомок = туда_не_знаю_куда;
    Узел<Тип>* левое_дитя = туда_не_знаю_куда;
    Узел<Тип>* правое_дитя = туда_не_знаю_куда;
    Узел<Тип>* будущий_брат = туда_не_знаю_куда;
    Узел<Тип>* прошлый_брат = туда_не_знаю_куда;

    Узел<Тип>(целина _знач) {
        знач = _знач;
    }
    бестолочь завязать(Узел<Тип>* узелок) {
        коли (узелок == это || узелок == туда_не_знаю_куда) {
            воздать;
        }
        будущий_брат = узелок;
        узелок->прошлый_брат = это;
    }
    бестолочь развязать_деревцо() {
        потомок = туда_не_знаю_куда;
        будущий_брат = туда_не_знаю_куда;
        прошлый_брат = туда_не_знаю_куда;
    }

    бестолочь развязать() {
        развязать_деревцо();
        коли (левое_дитя) {
            Узел<Тип>* текущ_узелок = левое_дитя;
            покуда (текущ_узелок) {
                текущ_узелок->потомок = туда_не_знаю_куда;
                текущ_узелок = текущ_узелок->будущий_брат;
            }
        }
        левое_дитя = туда_не_знаю_куда;
        правое_дитя = туда_не_знаю_куда;
    }

    бестолочь пусть_сойдутся_богатыри(Узел<Тип>* деревцо) {
        коли (левое_дитя == туда_не_знаю_куда) {
            левое_дитя = деревцо;
        } отнюдь {
            правое_дитя->завязать(деревцо);
        }
        правое_дитя = деревцо;
        деревцо->потомок = это;
        коли (пометь) {
            пометь = кривда;
        } отнюдь {
            чин++;
        }
    }

    Узел<Тип>* отъзеркалить() {
        суд_Перуна* отъзеркаленный_узелок = новь Узел<Тип>(знач);
        коли (левое_дитя) {
            Узел<Тип>* текущ_узелок = левое_дитя;
            покуда (текущ_узелок) {
                отъзеркаленный_узелок->пусть_сойдутся_богатыри(текущ_узелок->отъзеркалить());
                текущ_узелок = текущ_узелок->будущий_брат;
            }
        }

        воздать отъзеркаленный_узелок;
    }
};

свет_мой_зеркальце<скажи Тип>
семейство ФибоначчиеваРощица {
    Узел<Тип>* старший_братец = туда_не_знаю_куда;
    Узел<Тип>* младший_братец = туда_не_знаю_куда;
    Узел<Тип>* малый_узелок = туда_не_знаю_куда;
    полк<Узел<Тип>*> чины;

    розсуд пуст_ли() приказ_княжий {
        воздать старший_братец == туда_не_знаю_куда;
    }

    бестолочь поменять_малый_узелок(Узел<Тип>* узелок) {
        коли (узелок == туда_не_знаю_куда) {
            воздать;
        }
        коли (малый_узелок == туда_не_знаю_куда) {
            малый_узелок = узелок;
        } отнюдь коли (малый_узелок->знач > узелок->знач) {
            малый_узелок = узелок;
        }
    }

    бестолочь вставить_в_семью(Узел<Тип>* узелок) {
        коли (узелок == туда_не_знаю_куда) {
            воздать;
        }
        коли (узелок->пометь) {
            узелок->пометь = кривда;
            узелок->чин--;
        }
        узелок->потомок = туда_не_знаю_куда;
        узелок->будущий_брат = туда_не_знаю_куда;
        поменять_малый_узелок(узелок);
        коли (пуст_ли()) {
            старший_братец = узелок;
        } отнюдь {
            младший_братец->завязать(узелок);
        }
        младший_братец = узелок;
    }
    бестолочь пусть_сойдутся_богатыри(ФибоначчиеваРощица* фибоначчиева_рощица) {
        коли (пуст_ли()) {
            старший_братец = фибоначчиева_рощица->старший_братец;
            младший_братец = фибоначчиева_рощица->младший_братец;
            малый_узелок = фибоначчиева_рощица->малый_узелок;
        } отнюдь коли (!фибоначчиева_рощица->пуст_ли()){
            младший_братец->завязать(фибоначчиева_рощица->старший_братец);
            младший_братец = фибоначчиева_рощица->младший_братец;
            поменять_малый_узелок(фибоначчиева_рощица->малый_узелок);
        }
    }
    бестолочь перестроить_хуторок() {
        Узел<Тип>* текущ_узелок = старший_братец;
        Узел<Тип>* будущий_узелок;
        Узел<Тип>* узелок1;
        Узел<Тип>* узелок2;
        старший_братец = туда_не_знаю_куда;
        младший_братец = туда_не_знаю_куда;
        малый_узелок = туда_не_знаю_куда;
        покуда (текущ_узелок) {
            будущий_узелок = текущ_узелок->будущий_брат;

            текущ_узелок->развязать_деревцо();
            узелок1 = текущ_узелок;
            покуда (текущ_узелок->чин >= чины.велико()) {
                чины.внедрить_в_полк(туда_не_знаю_куда);
            }
            узелок2 = чины[текущ_узелок->чин];

            покуда (узелок2) {
                чины[узелок2->чин] = туда_не_знаю_куда;
                узелок2->развязать_деревцо();

                коли (узелок1->знач > узелок2->знач) {
                    меняло(узелок1, узелок2);
                }

                узелок1->пусть_сойдутся_богатыри(узелок2);
                покуда (узелок1->чин >= чины.велико()) {
                    чины.внедрить_в_полк(туда_не_знаю_куда);
                }
                узелок2 = чины[узелок1->чин];
            }

            чины[узелок1->чин] = узелок1;
            текущ_узелок = будущий_узелок;
        }

        покуда (чины.велико() > 0) {
            вставить_в_семью(чины[чины.велико() - целковый]);
            чины.убрать_из_полка();
        }


    }


    Узел<Тип>* воздать_малого_богатыря() приказ_княжий {
        воздать малый_узелок;
    }

    Тип воздать_знач_малого_богатыря() приказ_княжий {
        воздать воздать_малого_богатыря()->знач;
    }

    бестолочь развязать(Узел<Тип>* узелок) {
        Узел<Тип>* потомок = узелок->потомок;
        коли (потомок != туда_не_знаю_куда) {
            коли (узелок == потомок->левое_дитя) {
                коли (узелок == потомок->правое_дитя) {
                    потомок->левое_дитя = туда_не_знаю_куда;
                    потомок->правое_дитя = туда_не_знаю_куда;
                } отнюдь {
                    потомок->левое_дитя = узелок->будущий_брат;
                    потомок->левое_дитя->прошлый_брат = туда_не_знаю_куда;
                }
            } отнюдь коли (узелок == потомок->правое_дитя) {
                потомок->правое_дитя = узелок->прошлый_брат;
                потомок->правое_дитя->будущий_брат = туда_не_знаю_куда;
            } отнюдь {
                узелок->прошлый_брат->завязать(узелок->будущий_брат);
            }
        } отнюдь {
            коли (узелок == старший_братец) {
                коли (узелок == младший_братец) {
                    старший_братец = туда_не_знаю_куда;
                    младший_братец = туда_не_знаю_куда;
                } отнюдь {
                    старший_братец = узелок->будущий_брат;
                    старший_братец->прошлый_брат = туда_не_знаю_куда;
                }
            } отнюдь коли (узелок == младший_братец) {
                младший_братец = узелок->прошлый_брат;
                младший_братец->будущий_брат = туда_не_знаю_куда;
            } отнюдь коли (узелок->прошлый_брат) {
                узелок->прошлый_брат->завязать(узелок->будущий_брат);
            }
        }
        узелок->развязать_деревцо();
    }

    Тип убрать_и_воздать_малого_богатыря() {
        Узел<Тип>* узелок = убрать_малого_богатыря();
        Тип знач = узелок->знач;
        казнь узелок;
        воздать знач;
    }

    Узел<Тип>* убрать_малого_богатыря() {
        коли (пуст_ли() || малый_узелок == туда_не_знаю_куда) {
            воздать туда_не_знаю_куда;
        }
        Узел<Тип>* узелок = малый_узелок;
        развязать(малый_узелок);

        Узел<Тип>* текущ_узелок = малый_узелок->левое_дитя;
        Узел<Тип>* будущий_узелок;
        покуда (текущ_узелок) {
            будущий_узелок = текущ_узелок->будущий_брат;
            вставить_в_семью(текущ_узелок);
            текущ_узелок = будущий_узелок;
        }
        узелок->развязать();
        перестроить_хуторок();
        воздать узелок;
    }

    ФибоначчиеваРощица* отъзеркалить() {
        суд_Перуна* фибоначчиева_рощица = новь ФибоначчиеваРощица();

        Узел<Тип>* текущ_узелок = старший_братец;
        покуда (текущ_узелок) {
            фибоначчиева_рощица->вставить_в_семью(текущ_узелок->отъзеркалить());
            текущ_узелок = текущ_узелок->будущий_брат;
        }

        воздать фибоначчиева_рощица;
    }

    Узел<Тип>* сыскать(Петр_Первый азъ, Узел<Тип>* узелок) приказ_княжий {
        коли (узелок == туда_не_знаю_куда) {
            воздать туда_не_знаю_куда;
        }
        коли (узелок->знач == азъ) {
            воздать узелок;
        }

        Узел<Тип>* получка = сыскать(азъ, узелок->левое_дитя);
        коли (получка) {
            воздать получка;
        }

        воздать сыскать(азъ, узелок->будущий_брат);
    }

    бестолочь унизить_знач(Петр_Первый азъ, Петр_Первый буки) {
        коли (пуст_ли() || азъ <= буки) {
            воздать;
        }
        Узел<Тип>* узелок = сыскать(азъ, старший_братец);
        коли (узелок == туда_не_знаю_куда) {
            воздать;
        }
        узелок->знач = буки;
        коли (узелок->потомок == туда_не_знаю_куда) {
            поменять_малый_узелок(узелок);
            воздать;
        }
        коли (узелок->потомок->знач <= узелок->знач) {
            воздать;
        }

        Узел<Тип>* потомок = узелок->потомок;
        развязать(узелок);
        вставить_в_семью(узелок);
        узелок = потомок;

        покуда (правда) {
            потомок = узелок->потомок;
            развязать(узелок);
            вставить_в_семью(узелок);
            узелок = потомок;

            коли (узелок == туда_не_знаю_куда) {
                бить_ящеров;
            }
            коли (!узелок->пометь) {
                узелок->пометь = правда;
                бить_ящеров;
            }
        }

    }

};

свет_мой_зеркальце<скажи Тип>
ФибоначчиеваРощица<Тип>* пусть_сойдутся_богатыри(
    ФибоначчиеваРощица<Тип>* фибоначчиева_рощица1,
    ФибоначчиеваРощица<Тип>* фибоначчиева_рощица2) {
    фибоначчиева_рощица1 = фибоначчиева_рощица1->отъзеркалить();
    фибоначчиева_рощица2 = фибоначчиева_рощица2->отъзеркалить();

    фибоначчиева_рощица1->пусть_сойдутся_богатыри(фибоначчиева_рощица2);

    воздать фибоначчиева_рощица1;
}


царь_батюшка_главный() {
    полк<ФибоначчиеваРощица<целина>*> рощицы;
    целина порядок, порядок2, азъ, буки;
    слово действо;

    покуда (внемлить >> действо) {
        коли (действо == "create") {
            рощицы.внедрить_в_полк(новь ФибоначчиеваРощица<целина>());
        } отнюдь коли (действо == "insert") {
            внемлить >> порядок >> азъ;
            рощицы[порядок]->вставить_в_семью(новь Узел<целина>(азъ));
        } отнюдь коли (действо == "extract-min") {
            внемлить >> порядок;
            коли (рощицы[порядок]->пуст_ли()) {
                молвить << "*" << прыг_скок;
                добить_ящеров;
            }
            целина знач = рощицы[порядок]->убрать_и_воздать_малого_богатыря();
            молвить << знач << прыг_скок;
        } отнюдь коли (действо == "decrease-key") {
            внемлить >> порядок >> азъ >> буки;
            рощицы[порядок]->унизить_знач(азъ, буки);
        } отнюдь коли (действо == "merge") {
            внемлить >> порядок >> порядок2;
            рощицы.внедрить_в_полк(пусть_сойдутся_богатыри(рощицы[порядок], рощицы[порядок2]));
        }
    }


    воздать ноль;
}


