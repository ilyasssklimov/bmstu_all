…

## Как выбрать web-фреймворк?

- Github rating;
- имеющийся опыт;
- актуальность;
- документируемость;
- **имеются специфические фичи;**
- аппаратная совместимость;
- **ЯП**;
- финансовые ограничения;
- удобство тестирования и сопровождения;
- **производительность**.



## Benchmark

benchmark $\ne$ performance test $\ne$ load test.

Параметры:

- request / second;
- serialization;
- network;
- количество активных сессий.



### Проверка, является ли число простым

```python
def is_prime(n: int) -> bool:
  ...
```

1. Полным перебором

2. $for \text{ "} n \text{"} \to for \text{ "}\sqrt{n}\text{"}$

    6k + 1

3. Тест Миллера

> В зависимости от реализации и ЯП время может сильно отличаться.



## Тестирование производительности (performance testing)

*Пример*.

8 часов, 400 rps   $\to$   response time, rejected count   $\to$

| percent 0.5 (median) | percent 0.8 | percent 0.9 | percent 0.95 | percent 0.99 |
| :------------------: | :---------: | :---------: | :----------: | :----------: |



---

[Лекция 3](https://github.com/ilyasssklimov/bmstu_all/tree/sem_07/sem_07/Testing/lections/lection_03.md) [Лекция 5](https://github.com/ilyasssklimov/bmstu_all/tree/sem_07/sem_07/Testing/lections/lection_05.md)
