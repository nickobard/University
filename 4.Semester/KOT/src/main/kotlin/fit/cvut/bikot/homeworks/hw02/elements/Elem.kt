package fit.cvut.bikot.homeworks.hw02.elements

import kotlin.random.Random

// Tento interface dedi od Any - tedy jakakoliv trida dedi od Any, pokud bude dedit od Elem, tak ma dvakrat tostring
interface Elem {
    val content: List<String>
    val width: Int
        get() = if (content.isEmpty()) 0 else content.first().length
    val height: Int
        get() = content.size

    infix fun above(that: Elem): Elem {
        return BasicElem(this.content + that.content)
//        return BasicElem(this.content.plus(that.content))
//        return BasicElem(this.content + that.content)
    }

    infix fun beside(that: Elem): Elem {
        val pairs = this.content zip that.content
        return BasicElem(pairs.map { it.first + it.second })
    }
}

fun Elem.widenRight(w: Int, c: Char = ' '): Elem {
    require(w > width)
    return this beside CharElem(c, w - width, height)
}

fun Elem.widenLeft(w: Int, c: Char = ' '): Elem {
    require(w > width)
    return CharElem(c, w - width, height) beside this
}

fun Elem.widenTop(w: Int, c: Char = ' '): Elem {
    require(w > width)
    return CharElem(c, height, w - width) above this
}

fun Elem.widenBottom(w: Int, c: Char = ' '): Elem {
    require(w > width)
    return this above CharElem(c, height, w - width)
}


// DU bonus string reader - musi se vyuzit - a ude

// Proto potrebujeme mit abstraktni, ktera spravne implementuje ten toString, protoze v interface to nejde
abstract class AElem : Elem {

    override fun toString(): String = content.joinToString(separator = "\n")
}


open class BasicElem(override val content: List<String>) : AElem() {
    init {
        require(content.all { it.length == content.first().length }) { "invalid" }
    }
}

class CharElem(c: Char, w: Int, h: Int) : BasicElem(List(h) { c.toString().repeat(w) })

class StringElem(s: String, w: Int, h: Int, padding: Char = ' ') : BasicElem(List(h) {
    val start = it * w
    val end = start + w - 1
    if (start >= s.length) {
        padding.toString().repeat(w)
    } else if (s.length <= end) {
        s.slice(IntRange(start = start, endInclusive = s.length - 1)) + padding.toString().repeat(end + 1 - s.length)
    } else {
        s.slice(IntRange(start = start, endInclusive = end))
    }
})

// function will recursively create the spiral of the depth.
// depth je pocet ramen spiraly - tedy pocet bloku
//
// U textu posledni rameno napise tolik, kolik tam zbylo. Proste to dotahne.
//
// Tato spirala ma 3 rameny - a a, b b b, c c c c
// Pocatek asi se nepocita do poctu ramen (a je to asi jedno)
//
//   a a b
//   x   b
//       b
// c c c c
//
// Implementacni poznamky
//
// na bonus - vezme na vstup textu a rozparsue jeho pomoci string readeru na bloky a udela z nich spiralu

fun spiralElem(depth: Int, randomChar: Boolean = false, defaultChar: Char = '*'): Elem {
    if (depth < 1)
        return CharElem(' ', 0, 0)
    var char = defaultChar
    if (randomChar)
        char = Random.nextInt(97, 122).toChar()
    if (depth == 1)
        return CharElem(char, 1, 1)
    val spiral = spiralElem(depth - 1, randomChar = randomChar)
    return extendSpiralElem(spiral = spiral, depth = depth, char = char)
}

fun extendSpiralElem(spiral: Elem, depth: Int, char: Char = 'x'): Elem =
    when (depth % 4) {

        1 -> {
            val widenedSpiral = spiral.widenTop(spiral.height + 1)
            CharElem(char, 1, widenedSpiral.height) beside widenedSpiral
        }

        2 -> {
            val widenedSpiral = spiral.widenRight(spiral.width + 1)
            CharElem(char, widenedSpiral.width, 1) above widenedSpiral
        }

        3 -> {
            val widenedSpiral = spiral.widenBottom(spiral.height + 1)
            widenedSpiral beside CharElem(char, 1, widenedSpiral.height)
        }

        0 -> {
            val widenedSpiral = spiral.widenLeft(spiral.width + 1)
            widenedSpiral above CharElem(char, widenedSpiral.width, 1)
        }

        else -> {
            throw IllegalArgumentException()
        }
    }

fun spiralElemFromString(s: String): Elem {
    val strReader = s.reader()
    val read = strReader.read()
    var spiral: Elem = StringElem(read.toChar().toString(), 1, 1)
    var i = 2
    var stop = false
    while (!stop) {
        var stringPortion = ""
        for (j in 0 until i) {
            val read = strReader.read()
            if (read == -1) {
                stop = true
                break
            }
            stringPortion += read.toChar()
        }
        spiral = extendSpiralElemFromString(spiral, stringPortion, i)
        i++
    }
    return spiral;
}

fun extendSpiralElemFromString(spiral: Elem, str: String, depth: Int): Elem =
    when (depth % 4) {

        1 -> {
            val widenedSpiral = spiral.widenTop(spiral.height + 1)
            StringElem(str.reversed(), 1, widenedSpiral.height) beside widenedSpiral
        }

        2 -> {
            val widenedSpiral = spiral.widenRight(spiral.width + 1)
            StringElem(str, widenedSpiral.width, 1) above widenedSpiral
        }

        3 -> {
            val widenedSpiral = spiral.widenBottom(spiral.height + 1)
            widenedSpiral beside StringElem(str, 1, widenedSpiral.height)
        }

        0 -> {
            val widenedSpiral = spiral.widenLeft(spiral.width + 1)
            widenedSpiral above StringElem(str.reversed(), widenedSpiral.width, 1)
        }

        else -> {
            throw IllegalArgumentException()
        }
    }


fun main() {
    val e1 = BasicElem(List(3) { "${it}xxx" })
//    arrayOf() - timto lze udelat
    val e2 = BasicElem(listOf("xxxx", "yyyy", "zzzz"))
    println(e1)
    println("------------------------------------------")
    println(e2)
    println("------------------------------------------")
    println(e1 above e2)
    println("------------------------------------------")
    println(e1 beside e2)
    println("------------------------------------------")
    println(CharElem('*', 3, 4))
    println("------------------------------------------")
    println(e1.widenRight(6, '*'))
    println("------------------------------------------")

    var e3: Elem = CharElem('x', 1, 1)
    e3 = e3.widenRight(e3.width + 1)
    e3 = CharElem('a', e3.width, 1) above e3
    e3 = e3.widenBottom(e3.height + 1)
    e3 = e3 beside CharElem('b', 1, e3.height)
    println(e3)
    println("------------------------------------------")
    println("------------------------------------------")

    println(spiralElem(10))


    println("------------------------------------------")
    println("------------------------------------------")

    println(StringElem(s = "avada, kedavra", w = 1, h = 20, padding = ' '))

    println("------------------------------------------")
    println("------------------------------------------")
    println(
        spiralElemFromString(
            "Po celou dobu železniční přepravy bataliónu, který měl sklízet válečnou slávu, až projde pěšky od Laborce východní Haličí na front, vedly se ve vagónu, kde byl jednoroční dobrovolník a Švejk, opět podivné řeči, víceméně velezrádného obsahu."
        )
    )
}