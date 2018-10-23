# tpj-parser

## Linux

### Dependecies

* cmake
* gcc
* g++ (gcc-g++ on fedora)

### Build

* mkdir build
* cd build
* cmake ..
* make
* make test

### Example input

```c++
#include lrkv;

int main(){
  Engine L;
  Track T;
  Switch KuV1, KuV2, KuV5, KuV6;
  KuV1 = new Switch("Ku V1");
  KuV2 = new Switch("Ku V2");
  KuV5 = new Switch("Ku V5");
  KuV6 = new Switch("Ku V6");
  T=new Track;
  T->pridej(345);
  T->pridej(346);
  T->pridej(347);
  T->pridej(348);
  T->pridej(349);

  KuV1->nastavpolohu("+");
  if (KuV2->poloha=="-") {KuV2->prehod();}

  L=new Engine("Bardotka");
  L->zmensmer();
  for (int i=1; i<=14; i++) {L->jed(i); cekej(2);}
  while (!T->usek[349].jeobsazen) {cekej(1);}
  L->jed(0);
  return 0;
}
```
