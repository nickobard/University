import fit.cvut.bikot.homeworks.hw03.postfix_visitor.*
import java.util.*

interface Visitor {
    fun visit(e: Expr)
    fun printResult()
}

val Expr.priority
    get() = when (this) {
        is BinaryOperation -> operator.priority
        else -> 0
    }

class InfixVisitor : Visitor {
    val infix = Stack<String>()

    override fun visit(e: Expr) {
        when (e) {
            is IntLit -> infix.push(e.toString())
            is UnaryOperation -> {
                e.operand.visited(this)
                infix.push("(${e.operator}${infix.pop()})")
            }

            is BinaryOperation -> {
                e.rhs.visited(this)
                if (e.rhs.priority > e.operator.priority)
                    infix.push("(${infix.pop()})")

                e.lhs.visited(this)
                if (e.lhs.priority > e.operator.priority)
                    infix.push("(${infix.pop()})")

                infix.push("${infix.pop()} ${e.operator} ${infix.pop()}")
            }

            else -> error("$e")
        }
    }

    override fun printResult() {
        println(infix.peek())
    }
}

class PostfixVisitor : Visitor {
    val postfix = StringBuilder()
    override fun visit(e: Expr) {
        when (e) {
            is IntLit -> postfix.append(e.toString())
            is UnaryOperation -> {
                postfix.append("0")
                e.operand.visited(this)
                postfix.append("${e.operator}")
            }

            is BinaryOperation -> {
                e.lhs.visited(this)
                e.rhs.visited(this)
                postfix.append("${e.operator}")
            }

            else -> error("$e")
        }
    }

    override fun printResult() {
        println(postfix)
    }
}

fun BinaryOperation.evaluate(lhs: Expr, rhs: Expr) = when (operator) {
    Operator.PLS -> lhs.value + rhs.value
    Operator.MNS -> lhs.value - rhs.value
    Operator.MLT -> lhs.value * rhs.value
    Operator.DIV -> if (rhs.value != 0) lhs.value / rhs.value else error("Division by zero is undefined.")
}

fun UnaryOperation.evaluate(operand: Expr) = when (operator) {
    Operator.PLS -> operand.value
    Operator.MNS -> -operand.value
    else -> error("Invalid operator $operator")
}

class EvalVisitor : Visitor {
    val result = Stack<IntLit>()
    override fun visit(e: Expr) {
        when (e) {
            is IntLit -> result.add(IntLit(e.value))
            is UnaryOperation -> {
                e.operand.visited(this)
                result.push(IntLit(e.evaluate(result.pop())))
            }

            is BinaryOperation -> {
                e.lhs.visited(this)
                e.rhs.visited(this)
                result.push(IntLit(e.evaluate(rhs = result.pop(), lhs = result.pop())))
            }

            else -> error("$e")
        }
    }

    override fun printResult() {
        println(result.peek())
    }

}