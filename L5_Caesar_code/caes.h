#ifndef __CAESAR_H__
#define __CAESAR_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <gmp.h>
#include <locale.h>

#define _L(x)               (L##x)
#define _UPPERCASE(x)       (x - 32)
#define DEF_ALPH_LEN        33
#define DEF_STR_LEN         4096
//#define DEF_ALPH_PROB       L"оетаинрвсплкдмуыбьчжгяйхзцюэшщфъё"
// #define DEF_STR             \
// L"Вмз к шъмл удюэ дяьую. Рюььяж фдкышд — вмз дшичалмюм «юъъкышмдкхьзъмк кьйздыюскк» ышнрч фзучфюмшаоык к фдзрюцсюык з ъзъмзоькк фдзрчускк. Мюузж дяьзу кьзерю к ьюияцюпм «щюдюэзаузж». Уюу къфдюцкмл щюдюэзауч. Шъмл ьшъузалуз дяьзхьяэ фзрэзрзц рао къфдюцашько щюдюэзаук. Фшдцяж зъьзцяцюшмъо ью дшфчмюскк фдзрюцсю. Кршо ц мзы, хмз шъак зь фзъашрзцюмшальз езцздкм фзучфюмшаоы фдюцрч з уюхшъмцш цкрншмзц, мз ызншм июдющзмюмл дшфчмюскп хшъмьзез ршалсю. Кышо мюучп дшфчмюскп, зь ызншм фдзрюцюмл цяъзузуюхшъмцшььяш цкрншмя фз щзашш цяъзузж сшьш, мюу уюу фзучфюмшак щчрчм шыч цшдкмл, к дяьзу ъмюьшм щзашш вййшумкцьяы. Вмз мз дющзмюшм, мз ьшм — ц июцкъкызъмк зм щзашш мзхьяэ дяьзхьяэ чъазцкж. Узьшхьз, шъак фзучфюмшак к ъюык ц ъкаюэ зфдшршакмл уюхшъмцз мзцюдю, вмзм ышмзр ьш ъдющзмюшм. Ьз ц апщзы ъачхюш фдзкицзркмшал ьш ызншм ъдюич нш фзачхкмл эздзбчп дшфчмюскп. Вмз иьюхкм, хмз шыч ьчньз фдзрюцюмл щзашш уюхшъмцшььяш цкрншмя ию щзашш ькиучп сшьч, фзую фзучфюмшак ьш фзжычм, хмз кы езцздом фдюцрч. Вмз чъазньошм фзоцашькш хшъмьяэ фдзрюцсзц ью дяьуш. Рдчеюо фзмшьскюальюо фдзщашыю ъзъмзкм ц мзы, хмз фдзрюцшс, рюнш шъак фдшнрш зь щяа фдюцркц, щзалбш ьш кышшм ъмкычаю фдзрзанюмл щямл хшъмьяы, шъак эзхшм фзукьчмл дяьзу (ьюфдкышд, ки-ию ъзудютшько фдзрюн). Ц вмзы ъачхюш шыч ездюирз азекхьшж щяаз щя зщыюьчмл сшачп мзафч апршж, ю июмшы чжмк ъ дяьую. Мюу хмз дшфчмюско ьш дющзмюшм ц ьюхюаш к ц узьсш дяьзхьзж ршомшальзъмк фдзрюцсю. Дшфчмюскзььяж фзрэзр мюунш ьш дющзмюшм ц ъачхюоэ, шъак фзучфюмшак ьш цшрчм рша ъ зрьзж к мзж нш узыфюькшж, акщз уюмшездко фдзрчускк ъакбузы ьзцю к ьш фдшрзъмюцаошм цзиызньзъмк ъзирюмл дшфчмюскп. Кышььз мюукш фдзщашыя къфямяцюпм эюжмшу-дяьук цдзрш щкмузкь-щкдн. Рдчезж дяьзхьяж фзрэзр — вмз еюдюьмкк. Кршо ъзъмзкм ц мзы, хмз фдзрюцшс рюём еюдюьмкп фзучфюмшап ц мзы, хмз шъак цкрншм зуюншмъо фазэкы, фдзрюцшс фдшрзъмюцкм июышьч как цшдьём ршьлек. Вмз эздзбз дющзмюшм рз зфдшршаёььзез ызышьмю, ьз к мчм шъмл фдзщашыю: еюдюьмко — вмз мзнш фдзрчум, узмздяж мзнш щяцюшм ькиузез к цяъзузез уюхшъмцю. Ц ъачхюш ькиузуюхшъмцшььзж еюдюьмкк фдзрюцшс ькхшез ьш ършаюшм, шъак ця оцкмшъл у ьшыч ъз ъазыюььяы мзцюдзы, змуюншмъо зм ъцзшез зщштюько, акщз июъмюцкм цюъ фдзэзркмл хшдши ъчткж щпдзудюмкхшъукж узбыюд. Ышдя дшечакдзцюько. Мюукы зщдюизы, шъак щюдюэзаую дюидюъаюъл, ю дяьзхьяш фзрэзря ьш дющзмюпм рао зфдшршаёььзез дяьую, мзерю ью фзызтл ызншм фдкрмк дшечакдзцюькш. Ызньз цяршакмл мдк ъфзъзщю, узмздяык зьз ъфзъзщьз дшбкмл вмч фдзщашыч. Фшдцяж — дшечакдзцюькш ызншм мдшщзцюмл дюъудямко рюььяэ. Ьюфдкышд, мдшщзцюмл, хмзщя цъш цкрншмя кышак ыюдукдзцуч з уюхшъмцш, ю мюунш ьюаюеюмл ью йкдыч бмдюй ию азнл. Вмз фдшрзъмюцкм фзучфюмшап ьшрзъмюпткш ъцшршько. Цмздзж фзрэзр у дшечакдзцюькп — вмз цьшрдомл ъмюьрюдмя уюхшъмцю, хмзщя цкрншм ьш ызе фдзрюцюмлъо, шъак ьш фдзбёа къфямюькж ью уюхшъмцз, ю ъюы ъмюьрюдм зщшъфшхкцюа фдзэзнршькш мзалуз уюхшъмцшььяэ цкрншмзц. Вмз мюунш фдкцшаз щя у фдкъчмъмцкп ью дяьуш мзалуз зрьзез мкфю цкрншмзц, ьз мшфшдл вмз щяак щя уюхшъмцшььяш фдзрчумя (шъак дшечакдзцюькш дющзмюшм, уюу рзаньз). Мдшмкж ъфзъзщ — вмз зщоиюмл цъшэ фдзрюцсзц цяфчъуюмл еюдюьмкк, ю июмшы зщшъфшхкцюмл кэ къфзаьшькш, хмзщя фдзрюцся цъшерю ршднюак рюььзш ъазцз. Цъш вмк йздыя дшечакдзцюько, узьшхьз, ызечм к ьш ъдющзмюмл — ьюфдкышд, дющзмюмл ьш мюу, уюу июрчыюьз, щямл ьшфдюцкальз ьюфкъюььяык как ьшцшдьз фдкышьёььяык, ю мюунш зщдшышьомл фдзрюцсзц. Ьз фз удюжьшж ышдш шъмл цшдзомьзъмл мзез, хмз мюузж мкф дшечакдзцюько ъызншм къфдюцкмл ьшчрюхьяж дяьзу. Апрк, цяъмчфюпткш ию дшечакдзцюькш щкмузкь-щкдн, хюъмз ьюияцюпм кэ щюдюэзауюык."

#define DEF_ALPH_PROB L"отеаинрвслкпмдуычьбгзяхжйюшэёщцфъ"
#define DEF_STR             \
L"Ачяруцдд, ачжчибг шуягхупж жуачг юживажвидичщуцдг, ечтыцб ючюжущткжй чжхгж ч рчечшиджгтйцчя рчщгегцдд. Нжу дцэчияуодк жуаыг рчюжвругж щ риущджгтйюжщгццбг лушб еуццбф д ячыгж ридщгюжд а цухутв иуюютгечщуцдк. Щ огтчя ыг жиглчщуцдк шущдюкж чж южиуцб. Цуюжчкъдя яб цдачдя члиушчя цг еуёя пидедхгюадф игачягцеуодм ч цгчлфчедячюжд рчечлцбф егмюжщдм д цг чрдюбщугя дф члиуш. Еуццчг члювыегцдг ридшщуцч еужй рчцкждг ч жчя, ауадг жиглчщуцдк цутусугж шуачцчеужгтйюжщч РЧЕ. Ютгевгж рчяцджй, хжч риущджгтйюжщу — ауа щ ЮЗУ, жуа д щ еивсдф южиуцуф, щчюридцдяупж риущдту РЧЕ аиумцг югийёшцч. Нжч цг жг риущдту, ачжчибг ячыцч шуричюжч цуивзужй д иушлдиужйюк, жчтйач гютд щтуюжд юч щигягцгя члиужкж цу нжч щцдяуцдг. Лджачдц-эдияб шуаибщутд — дцчсеу щигягццч, дцчсеу цуючщюгя. Ригеридцдяужгтгм уигюжчщбщутд д юуыутд щ жпийяв шу цгщбрчтцгцдг нждф риущдт. Нжч жуаук члтуюжй, щ ачжчичм риущджгтйюжщч игзджгтйцч д лгшыутчюжцч рчтйшвгжюк шуачцчя, д цгщуыцч, ауюугжюк егтчлджачдцу дтд щгъгюжщгццчм щутпжб. Риущджгтйюжщч дюрчтйшвгж нжд шуачцб ричждщ лджачдц-эдия ю жгф рчи, ауа шуягждтч, хжч лджачдц ечюжужчхцч вечлгц етк чжябщуцдк егцгс. Гютд щб фчжджг чжаибжй ющчм лдшцгю, хгигш ачжчибм лвевж ричфчеджй лчтйздг чльгяб егцгс, ютгевгж юцухуту рчючщгжчщужйюк ю пидюжчя, ачжчибм иушлдиугжюк щ нждф риущдтуф. У жгргий рикяч рчсчщчидя ч ютчщг цу лващв и — игсвтдичщуцдд. Игсвтдичщуцдг хуюжч дяггж евицвп игрвжуодп, чючлгццч юигед тплджгтгм лджачдцу. Члбхцч юхджупж, хжч игсвткжчи — нжч лпичаиуждхгюаук яуздцу, ачжчиук цдхгсч цг юябютдж щ жчя, хжч нжч шу лдшцгю д хгя чц шуцкж, щтгшугж д щюё юрвжбщугж. Нжч жчтйач члвшу, нжч стврч д лгююябютгццч. Жуадг ечщчеб шщвхуж ечщчтйцч хуюжч, д дф тгсач рчцкжй — шухуюжвп чцд юриущгетдщб. Цч а нжчяв яб щчшщиуъужйюк лчтйзг цг лвегя. Щ еуццчя иушегтг яб рчсчщчидя ч жчя, рчхгяв игсвтдичщуцдг дцчсеу лбщугж чриущеуцч, рчюачтйав нжчж уисвягцж шухуюжвп чаушбщугжюк цгрчцкжбя. Счщчик рч риущег, жч, хжч яб цу ричжкыгцдд лчтйзгм хуюжд нжчм тгаодд счщчидя ч жчя, рчхгяв игсвтдичщуцдг ячыгж лбжй фчичзгм щгъйп, гъё цг ечтыцч юхджужйюк урчтчсдгм здичачсч игсвтдичщуцдк. Яб егтугя нжч рчжчяв, хжч фчждя виущцчщгюджй здичач иуюричюжиуцёццбг щ юччлъгюжщг ечщчеб ч жчя, хжч игсвтдичщуцдг — нжч щюгсеу ртчфч дтд стврч щ юуячм ющчгм ювжд. Чюцчщцчм ечщче щ юрчиг ч игсвтдичщуцдд шщвхдж жуа: ачсеу ибцад руеупж д щбеупж ртчфвп ечфчецчюжй, ю хгя ючстуюцб щюг вхуюжцдад, жчсеу игсвтдичщуцдг ячыгж втуеджй нжв ричлтгяв. Жуа хжч чюцчщцук дегк щ ечщчеуф шу игсвтдичщуцдг, гютд чцд щччлъг цвыцб, ючюжчдж щ жчя, хжч ибцад цг щюгсеу ридцчюкж ыгтугябм игшвтйжуж. Луиуфчтау. Рчсчщчидя ч жчя, ауа ибцча ячыгж цг юриущджйюк ю иулчжчм цу атуююдхгюачя ридягиг рче цушщуцдгя «луиуфчтау» (щ чидсдцутг lemons market – цу ютгцсг ибцча ричеуыд рчегиыуццбф ущжчячлдтгм юч юаибжбяд цгечюжужауяд — ридя.рги). Ригеюжущдя юглг, хжч гюжй цгадм ибцча «щдеыгжчщ» - цгачгсч жчщуиу, ачжчибм рчаврупж д ричеупж. Юауыгя, щдеыгжб лбщупж фчичзгсч д ртчфчсч аухгюжщу. Щбючачаухгюжщгццбм щдеыгж цгюачтйач ечичыг ричдшщчеджй, цч чц цуяцчсч твхзг етк жчсч, ажч гсч аврдж. Жуа хжч рчавружгтд ригерчхджупж щбючачаухгюжщгццбг щдеыгжб. Гютд ибцча иулчжугж фчичзч, гютд чц щ начцчядхгюачя юябютг нээгаждщгц, цу цёя лвевж ригеюжущтгцб щ чюцчщцчя щбючачаухгюжщгццбг щдеыгжб. Нжч ричдюфчедж рчжчяв, хжч фчжк жуачм щдеыгж д ечичыг, рчавружгтй лвегж ригерчхджужй дягццч гсч, д шуртуждж шу цгсч лчтйзг. Жуа хжч ю дшщгюжцбяд чсчщчиауяд щбфче в ибцау лвегж вюргзцбя. Ю еивсчм южчичцб, ечрвюждя, хжч рчавружгтд цг ячсвж чжтдхджй фчичздм щдеыгж чж ртчфчсч еч рчаврад. Атуююдхгюадм ридяги — нжч рчегиыуццчг ущжч. Щб юячжиджг цу жуавп яуздцв, д чцу щбсткедж ечщчтйцч фчичзч, цч цу юуячя егтг щб цг ячыгжг ю вщгигццчюжйп юаушужй, хжч цушущжиу чцу цг ютчяугжюк, дтд хжч ричютвыдж гъё ечтсчг щигяк. Едтги цущгицкау щ авиюг, хжч яуздцу лиуачщуццук, цч щб, ауа рчавружгтй, щике тд шуягжджг иушцдов. Рчевяугя ч жчя, хжч ридщчедж тпегм цу луиуфчтав. Ауа рчавружгтй, щб цг фчжджг ртужджй тдзцгсч шу щбючачаухгюжщгццбм щдеыгж — ричюжч рчжчяв, хжч цг щдеджг иушцдоб. Еуыг гютд едтги аткцёжюк, хжч яуздцу лгшвригхцу, д ргигртужджй цвыцч жчтйач южч ечттуичщ, в щую цгж югийёшцбф чюцчщуцдм гяв щгиджй. Щ игшвтйжужг ричдшщчеджгтд цг рчтвхупж ечрчтцджгтйцчм ридлбтд шу ричеуыв щбючачаухгюжщгццчсч щдеыгжу — цучлчичж, чцд жгиркж влбжад, ричеущук жуадг щдеыгжб, жуа ауа ричдшщчеджй гсч ечичыг, у ечрчтцджгтйцбф егцгс чцд цг ридцчюдж. Рчнжчяв ибцча шуюжигщугж щ ючюжчкцдд, ачсеу ричдшщчекжюк жчтйач цдшачаухгюжщгццбг щдеыгжб, ачжчибяд рчавружгтд юиущцджгтйцч цгечщчтйцб."

struct letter
{
    wchar_t c_symb;
    wchar_t ec_symb;
    float prob;
};

typedef struct letter Letter;

#endif
