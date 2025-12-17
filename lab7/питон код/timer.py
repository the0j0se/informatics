import time
from typing import List

def scalar_product(a: List[float], b: List[float]) -> float:
    """Скалярное произведение двух векторов одинаковой длины."""
    return sum(x * y for x, y in zip(a, b))

def measure_total_time(iters: int, a: List[float], b: List[float]) -> None:
    start = time.perf_counter()

    for _ in range(iters):
        scalar_product(a, b)

    elapsed = time.perf_counter() - start
    print(f"Итераций: {iters}")
    print(f"Общее время: {elapsed:.6f} секунд")
    print("-" * 40)

if __name__ == "__main__":
    a = [1.0, 2.0, 3.0]
    b = [4.0, 5.0, 6.0]

    for iters in (1_000_000, 10_000_000, 100_000_000):
        measure_total_time(iters, a, b)
