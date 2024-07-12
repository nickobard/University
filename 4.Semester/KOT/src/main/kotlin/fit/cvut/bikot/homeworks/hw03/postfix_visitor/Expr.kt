package fit.cvut.bikot.homeworks.hw03.postfix_visitor

import EvalVisitor
import InfixVisitor
import PostfixVisitor
import Visitor

interface Expr {
    val value: Int

    companion object {
        val Zero = IntLit(0)
        val One = IntLit(1)
        val Two = IntLit(2)
    }

    fun visited(v: Visitor){
        v.visit(this)
    }
}


enum class Operator(val symbol: String, val priority: Int) {
    PLS("+", 2), MNS("-", 2), MLT("*", 1), DIV("/", 1);

    override fun toString() = symbol
}

data class IntLit(override val value: Int) : Expr {
    override fun toString() = "$value"
}

data class UnaryOperation(val operator: Operator, val operand: Expr) : Expr {
    override val value
        get() = when (operator) {
            Operator.PLS -> operand.value
            Operator.MNS -> -operand.value
            else -> error("Invalid operator $operator")
        }


    override fun toString(): String = "$operator$operand"
}

data class BinaryOperation(val operator: Operator, val lhs: Expr, val rhs: Expr) : Expr {
    override val value
        get() = when (operator) {
            Operator.PLS -> lhs.value + rhs.value
            Operator.MNS -> lhs.value - rhs.value
            Operator.MLT -> lhs.value * rhs.value
            Operator.DIV -> if (rhs.value != 0) lhs.value / rhs.value else error("Division by zero is undefined.")
        }

    override fun toString(): String = "($lhs $operator $rhs)"
}

fun Expr.print() {
    println("$this = ${this.value}")
}

fun main(args: Array<String>) {

    val e = IntLit(3)
    println(e)
    val unmns = UnaryOperation(Operator.MNS, e)
    println(unmns)
    val binaryOperatorPLS = BinaryOperation(Operator.PLS, e, unmns)
    val binaryOperatorMNS = BinaryOperation(Operator.MNS, e, binaryOperatorPLS)
    val binaryOperatorMLT = BinaryOperation(Operator.MLT, binaryOperatorMNS, e)
    binaryOperatorMLT.print()

    println('-'.toString().repeat(40))


    val iv = InfixVisitor()
    binaryOperatorMLT.visited(iv)
    println(iv.infix.pop())

    println('-'.toString().repeat(40))

    val postVis = PostfixVisitor()
    binaryOperatorMLT.visited(postVis)
    println(postVis.postfix)

    println('-'.toString().repeat(40))
    val evalVis = EvalVisitor()
    binaryOperatorMLT.visited(evalVis)
    evalVis.printResult()

}