import fit.cvut.bikot.homeworks.hw01.heapsort.PriorityQueue

fun main(args: Array<String>) {
    val pq = PriorityQueue(1.0, 333.0, 2.0, 10.0, 8.0, 4.0, 4.0)
    println(pq)
    pq.add(0.5)
    pq.add(1111.1)
    println(pq)
    for (e in pq) println(e)
    pq.add(1.1)
    pq.add(1111.1)
    println(pq)
    while (!pq.isEmpty()) {
        println(pq.poll())
        println(pq)
    }
    val arrToSort = doubleArrayOf(2.3, 1.3, 100.0, -23.4, 42.0)
    val pq2 = PriorityQueue(*arrToSort)
    val sorted = pq2.heapSort()
    println(sorted.joinToString(separator = ", ", prefix = "[", postfix = "]"))
}