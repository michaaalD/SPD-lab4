#include <iostream>
#include<fstream>
#include <string>

struct task
{
  public:
    int ID;
    int r;
    int p;
    int q;
};

void task_swap(task& a, task& b)
{
  std::swap(a.ID, b.ID);
  std::swap(a.p, b.p);
  std::swap(a.q, b.q);
  std::swap(a.r, b.r);
}


int schrage(int n, task* T, int* X)
{
  int ND[100], D[100];							//ND - tablica zadań niedostępnych  D - tablica zadań dostępnych
  int nd = n, d = 0, w = 0;		// nd - liczba zadań niedostępnych  d-tablica zadań dostępnych  w-liczba zadań wykonanych 
  int  t = 0, cmax = 0;			//t - obecna jednostka czasu  cmax-długość najdłuższego uszeregowania
  for (int i = 0; i < n; i++)
  {
    ND[i] = i;
  }
  for (int i = 0; i < n - 1; i++)			//sortowanie tablicy zadań niedostęnych malejąco po r
  {
    for (int j = 0; j < n - 1; j++)
    {
      if (T[ND[j]].r < T[ND[j + 1]].r)
      {
        std::swap(ND[j], ND[j + 1]);
      }
    }
  }
  while (w != n)					//jeśli są zadania niewykonane
  {
    if (nd != 0)				//jeśli są jeszcze zadania niedostępne
    {	
      if (T[ND[nd - 1]].r <= t)		//jeśli jest jakieś task które przyszło
      {
        D[d] = ND[nd - 1];
        d++;
        nd--;
        for (int k = d - 1; k > 0; k--)			//sortowanie tablicy zadań dostępnych rosnąco po q
        {
          if (T[D[k]].q < T[D[k - 1]].q)
          {
            std::swap(D[k], D[k - 1]);
          }
        }
        continue;
      }
    }
    if (d != 0)			//jeśli są zadania dostępne
    {
      X[w] = D[d - 1];
      t += T[X[w]].p;
      cmax = std::max(cmax, t + T[X[w]].q);
      d--;
      w++;
      continue;
    }
    if (d == 0 && T[ND[nd - 1]].r > t)			//jeśli jest jakiaś przerwa w pracy to ją przeskocz
    {
      t = T[ND[nd - 1]].r;
    }
  }
  return cmax;
}
int schrage_divide(int n, task* T)
{
  int ND[100];
  int D[100];
  int pom[100];
  int nd = n;
  int d = 0;
  int  t = 0;
  int cmax = 0;
  int poz = 100;
  int ile_zr = 0;
  for (int i = 0; i < n; i++)
  {
    pom[i] = T[i].p;
  }
  for (int i = 0; i < n; i++)
  {
    ND[i] = i;
  }
  for (int i = 0; i < n - 1; i++)			
  {
    for (int j = 0; j < n - 1; j++)
    {
      if (T[ND[j]].r < T[ND[j + 1]].r)
      {
        std::swap(ND[j], ND[j + 1]);
      }
    }
  }
  while (nd != 0 || d != 0)
  {
    if (nd != 0)
    {
      if (T[ND[nd-1]].r <= t)
      {
        D[d] = ND[nd - 1];
        d++;
        nd--;
        for (int k = d - 1; k > 0; k--)			
        {
          if (T[D[k]].q < T[D[k - 1]].q)
          {
            std::swap(D[k], D[k - 1]);
          }
        }
        if (poz != 100)
        {
          if (T[D[d - 1]].q > T[poz].q)
          {
            D[d] = poz;
            std::swap(D[d], D[d - 1]);
            d++;						
            poz = 100;
          }
        }
        continue;
      }
    }
    if (d != 0)
    {
      if (poz == 100)
      {
        poz = D[d - 1];
        d--;
      }
      if (nd != 0)
      {
        ile_zr = std::min(pom[poz], T[ND[nd - 1]].r - t);
      }
      else
      {
        ile_zr = pom[poz];
      }
      t += ile_zr;
      pom[poz] -= ile_zr;
      if (pom[poz]== 0)
      {
        cmax = std::max(cmax, t + T[poz].q);
        poz = 100;
      }
      continue;
    }
    if (d == 0 && nd != 0)
    {
      if (T[ND[nd - 1]].r > t)
      {
        t = T[ND[nd - 1]].r;
      }
    }
  }
  return cmax;
}
int main()
{
  int X[100];
  task T[100];
  std::string s = "data.00", s1, s2;
  std::ifstream f("data.txt");
  int n;
  for (int i = 0; i < 9; i++)			//pętla przechodząca przez każdy zbiór danych
  {
    s1 = s + std::to_string(i) + ":";
    while (s2 != s1)				//szukanie odpowiedniego zbioru danych
    {
      f >> s2;
    }
    f >> n;							//wczytywanie ilości zadań w danym zbiorze danych
    for (int j = 0; j < n; j++)		//wczytywanie parametrów kolejnych zadań
    {
      T[j].ID = j;
      f >> T[j].r >> T[j].p >> T[j].q;
    }
    std::cout << "| " << s1 << std::endl;
    std::cout << "| Podzial: " << schrage_divide(n, T) << std::endl;
    std::cout << "| Schrage: " << schrage(n, T, X) << std::endl;
    std::cout << "| Roznica: " << schrage(n, T, X) - schrage_divide(n, T) << std::endl;
    for (int i = 0; i < n; i++)
    {
      std::cout << X[i]+1 << " ";
    }
    std::cout <<std::endl<< "===========================================" <<std::endl;
  }
}
