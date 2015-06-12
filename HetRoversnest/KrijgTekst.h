#ifndef KRIJGTEKST_H
#define KRIJGTEKST_H

const char * KrijgTekst(const int hoofdstuk)
{
  switch (hoofdstuk)
  {
    case 1: 
    { 
      const static char tekst[] = 
        "De voettoch naar Zwartzand voert je zo'n vijfenzeventig kilometer "
        "over vlakten en heuvels naar het Westen; "
        "gelukkig zonder onaangename ontmoetingen. "
        "Uiteindelijk bereik je de kust en zie je de hoge stadsmuur die zwartzand omgeeft "
        "en de dichtopeengebouwde huizenklomp die de zee insteekt als een zwart onheilsteken. "
        "Schepen liggen voor anker in de haven en rook stijgt langzaam op uit de schoorstenen. "
        "Het ziet er vredig genoeg uit en pas als de wind van richting verandert, "
        "ruik je het verval om het briesje "
        "en het herinnert je aan de boze aard van dit beruchte oord. "
        "Terwijl je de stoffige weg noordwaards langs de kust naar de stadspoorten volgt,"
        "zie je de eerste angstaanjagende waarschuwingen: "
        "schedels op op houten staken, hongerende mannen in ijzeren kooien "
        "die aan de stadsmuur hangen en overal zwarte vlaggen. "
        "Als je de stadspoort nadert loopt er een koude rilling over je rug"
        "en instinctief grijp je het gevest van je slagzwaard om jezelf gerust te stellen. "
        "Bij de poort wordt je opgewacht door een lange wachter. Hij draagt een zwarte malienkolder en een ijzeren helm. "
        "Hij treedt naar voren, je de doorgang belemmerend met zijn piek en zegt: 'Wie waagt het onuitgenodigd naar Zwartzand te komen? "
        "Verklaar wat je hier te zoeken hebt of ga de weg terug die je gekomen bent.'. "
        "Wat doen je? "
        "[1] Tegen hem zeggen dat je naar Nicodemus gebracht wil worden? "
        "[2] Tegen hem zeggen dat je gestolen waar wil verkopen? "
        "[3] Hem snel aanvallen met je zwaard? "
       ;"
      return tekst; 
    }
    case 2: 
    { 
      const static char tekst[] = 
        "Je haalt de armband van je pols en gooit hem naar het aanstormende monster."
        "Hij komt terecht op zijn pantser en blijft er tegen aan plakken."
        "Je kijkt hoe de armband zich dwars door het pantser heenbrandt, het lichaam van de Reuzenduizendpoot in."
        "Rookt stijgt op uit het precies ronde gat en naarmate de armband zich dieper naar binnen brandt zie je aan de stuipstrekkende bewegingen van de Duizendpoot dat hij zijn doodsstrijd levert."
        "Tenslotte ligt hij stil en je slaagt erin je tussen zijn lichaam en het dak van de tunnel door te wringen."
        "Je loopt door de tunnel die ophoudt bij een ijzeren hek waardoorheen het rioolslijk stroomt."
        "[1]Als je het hek wilt forceren, ga dan door naar 377."
        "[2]Als je wilt teruglopen naar de ingang ga dan naar 174."  
      ;
      return tekst;
    }
    case 33: 
    { 
      const static char tekst[] = 
        "33"
      ;
      return tekst;
    }
    case 49: 
    { 
      const static char tekst[] = 
        "Als je je zwaard trekt, duikt de wachter naar rechts "
        "in een poging een kleine bel aan de muur van het wachthuis te luiden. "
      ;
      return tekst;
    }
    case 202: 
    { 
      const static char tekst[] = 
        "202"
      ;
      return tekst;
    }
  }
  return '\0';
}

#endif // KRIJGTEKST_H

