#include <iostream>
#include <string>

class Figura {
public:
  Figura(int przesuniecie, char znak)
      : przesuniecie_(przesuniecie), znak_(znak) {}

  void przesun(int o_ile) { przesuniecie_ += o_ile; }
  virtual void narysuj() const = 0;

  int przesuniecie() const { return przesuniecie_; }
  char znak() const { return znak_; }

private:
  // Liczba spacji miedzy lewym marginesem a figura
  int przesuniecie_;
  // Znak, ktorym jest rysowana figura
  char znak_;
};

class Trojkat : public Figura {
public:
  Trojkat(int wysokosc, int przesuniecie, char znak)
      : Figura(przesuniecie, znak), wysokosc_(wysokosc) {}

  void narysuj() const override;

private:
  // Liczba znakow wysokosci i dlugosci podstawy trojkata
  int wysokosc_;
};

void Trojkat::narysuj() const {
  int k;
  int liczba_znakow = przesuniecie() + 1;
  for (int w = 1; w <= wysokosc_; ++w) {
    for (k = 1; k <= przesuniecie(); ++k) {
      std::cout << ' ';
    }
    for (; k <= liczba_znakow; ++k) {
      std::cout << znak();
    }
    ++liczba_znakow;
    std::cout << "\n";
  }
}

class TrojkatZPodpisem : public Trojkat {
public:
  TrojkatZPodpisem(int wysokosc, int przesuniecie, char znak,
                   const std::string &podpis)
      : Trojkat(wysokosc, przesuniecie, znak), podpis_(podpis) {}

  void narysuj() const override {
    Trojkat::narysuj();
    std::cout << "\n" << podpis_ << "\n";
  }

private:
  // Podpis pod trojkatem
  std::string podpis_;
};

void narysuj(const Figura &f) { f.narysuj(); }

int main() {
  Trojkat t1(5, 3, '*');
  Figura *f = &t1;
  f->narysuj();
  TrojkatZPodpisem t2(7, 0, 'x', "trojkat");
  std::cout << "\n";
  narysuj(t2);
  t1.przesun(4);
  std::cout << "\n";
  narysuj(t1);
  return 0;
}