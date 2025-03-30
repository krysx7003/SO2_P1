# Systemy Operacyjne 2

## Teoria

Problem jedzących filozofów.

## Instrukcja

1. Kod przygotowany na systemy Linux (korzysta z biblioteki pthreads).
2. Gotowy plik wykonywalny znajduję się w katalogu build/release/ pod nazwą Proj_1.
3. Do całego projektu załączony jest CMakeLists.txt.
4. Aby wygenerować plik wykonywalny należ użyć komend:

        cmake -S . -B build/release -G "Unix Makefiles"
        cmake --build build/release
5. Przy uruchamianiu programu należy podać argument typu int będący liczbą filozofów. Np:

        ./Proj_1 5


## Źródła

1. <https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/>
2. <https://lass.cs.umass.edu/~shenoy/courses/spring04/677/readings/Chandy_drinking_phil.pdf>
3. <https://enomem.substack.com/p/the-drinking-philosophers-problem>
4. <https://www.geeksforgeeks.org/dining-philosophers-problem/>
5. <https://www.youtube.com/watch?v=-Qa1RqmXKG0>
6. <https://www.youtube.com/watch?v=Zp17-UDKM90>
7. <https://www.youtube.com/watch?v=hXKtYRleQd8>
