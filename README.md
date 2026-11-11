# ЛР4 - Связанные списки

Проект на C++17: однонаправленный список с bottom, двунаправленный список, вставка через InsertCell, сортированная вставка, поиск максимума, проверка сортировки, многопотоковый список планет (три логические цепочки указателей) и алгоритм черепахи и кролика.

**Важно:** многопотоковый список здесь означает несколько цепочек ссылок по разным критериям, а не параллельные потоки выполнения std::thread.

## Сборка

```bash
cmake -S . -B build
cmake --build build
./build/lab4
```

## Тесты

```bash
sudo apt install libgtest-dev
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Проверка памяти

```bash
valgrind --leak-check=full --error-exitcode=1 ./build/list_tests
```

## Документация

```bash
doxygen Doxyfile
```

Открыть `docs/html/index.html`.

## Docker

```bash
docker build -t lab4-lists .
docker run -it --rm lab4-lists
```
