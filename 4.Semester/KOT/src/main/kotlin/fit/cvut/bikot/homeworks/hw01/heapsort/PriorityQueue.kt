package fit.cvut.bikot.homeworks.hw01.heapsort

import java.util.Queue
import kotlin.NoSuchElementException

class PriorityQueue(vararg element: Double, maxSize: Int = 1000) : Queue<Double> {

    private val dataBuffer = Array(kotlin.math.max(element.size, maxSize)) { ind ->
        if (ind < element.size) element[ind] else 0.0
    }

    private fun data(offset: Int = 0) = dataBuffer.copyOfRange(offset, size)

    private var _size = element.size

    private val lastInd: Int
        get() = size - 1

    init {
        buildHeap(dataBuffer, lastInd)
    }

    fun heapSort(): Array<Double> {
        return Companion.heapSort(data(0), lastInd)
    }

    override val size: Int
        get() = _size

    override fun isEmpty() = size == 0

    fun isFull() = size == dataBuffer.size

    override fun toString() = data(0).joinToString(prefix = "[", postfix = "]")

    override fun remove(): Double {
        if (isEmpty()) throw NoSuchElementException()
        val max = dataBuffer[0]
        remove(0)
        return max
    }

    private fun remove(ind: Int) {
        dataBuffer[ind] = dataBuffer[lastInd]
        _size--
        bubbleDown(ind, dataBuffer, lastInd)
    }

    override fun poll(): Double? = try {
        remove()
    } catch (e: NoSuchElementException) {
        null
    }

    override fun add(element: Double): Boolean {
        if (isFull()) throw RuntimeException("isFull")
        dataBuffer[_size++] = element
        //   buildHeap(dataBuffer, lastInd)
        var ind = lastInd
        // Start from the bottom and bubbling down until hit the top.
        // Traversing through all parents to the root, and using bubble down there.
        do {
            ind = parentInd(ind)
            bubbleDown(ind, dataBuffer, lastInd)
        } while (ind > 0)
        return true
    }

    override fun element() = peek() ?: throw NoSuchElementException()

    override fun peek() = if (isEmpty()) null
    else dataBuffer[0]

    override fun addAll(elements: Collection<Double>): Boolean {
        var b = false
        for (e in elements) {
            b = b || add(e)
        }
        return b
    }

    override fun clear() {
        dataBuffer.fill(0.0)
        _size = 0
    }

    override fun iterator(): MutableIterator<Double> {
        return object : MutableIterator<Double> {
            var currInd = 0
            override fun hasNext() = currInd <= lastInd

            override fun next() = dataBuffer[currInd++]

            override fun remove() {
                TODO("Not yet implemented")
            }

        }
    }

    override fun remove(element: Double): Boolean {
        val ind = data().indexOf(element)
        remove(ind)
        return true
    }

    override fun containsAll(elements: Collection<Double>): Boolean {
        for (e in elements) {
            if (!contains(e)) return false
        }
        return true
    }

    override fun contains(element: Double) = element in data(0)

    override fun retainAll(elements: Collection<Double>): Boolean {
        TODO("Not yet implemented")
    }

    override fun removeAll(elements: Collection<Double>): Boolean {
        var b = false
        for (e in elements)
            b = b || remove(e)
        return b
    }

    override fun offer(p0: Double) = add(p0)

    /*
    Companion objects are just like singletons for this class. We can have them many, with specified or unspecified name.
    In java it would be static inner class at the place of companion object. So every method in static class is static,
    and you do not have to write everywhere static.

    Here is why to use companion objects in Kotlin
    https://medium.com/swlh/kotlin-basics-of-companion-objects-a8422c96779b#:~:text=So%20why%20use%20companion%20objects,use%20a%20regular%20object%20instead.

    companion objects are not lazy - they are loaded at the first usage of the outer class. Just objects are lazy initialized - only on direct use.

     */
    companion object {
        private fun leftChildInd(parentInd: Int) = parentInd * 2 + 1
        private fun parentInd(childInd: Int) = (childInd - 1) / 2

        fun swap(i: Int, j: Int, dataBuffer: Array<Double>) {
            val x = dataBuffer[i]
            dataBuffer[i] = dataBuffer[j]
            dataBuffer[j] = x
        }

        fun bubbleDown(topInd: Int, dataBuffer: Array<Double>, lastInd: Int) {
            if (topInd >= lastInd) return
            val leftChildInd = leftChildInd(topInd)
            if (leftChildInd > lastInd) return
            val rightChildInd = leftChildInd + 1
            val maxChildInd = if (rightChildInd > lastInd)
                leftChildInd
            else if (dataBuffer[leftChildInd] >= dataBuffer[rightChildInd])
                leftChildInd
            else rightChildInd
            if (dataBuffer[topInd] < dataBuffer[maxChildInd]) {
                swap(topInd, maxChildInd, dataBuffer)
                bubbleDown(maxChildInd, dataBuffer, lastInd)
            }
        }

        fun buildHeap(dataBuffer: Array<Double>, lastInd: Int) {
            for (ind in lastInd - 1 downTo 0)
                bubbleDown(ind, dataBuffer, lastInd)
        }

        fun heapSort(dataBuffer: Array<Double>, lastInd: Int): Array<Double> {
            val dataToSort = dataBuffer.copyOfRange(0, lastInd + 1).toDoubleArray()

            val pq = PriorityQueue(*dataToSort)
            val sorted = Array<Double>(pq.size) { _ ->
                pq.poll() ?: throw IndexOutOfBoundsException()
            }
            return sorted
        }

    }

}