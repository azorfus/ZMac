#	Simple Math expression evaluator written to
#	understand expression evaluation. Same method
#	is implemented in the main project.

running = True
tokens = []

class node:
	def __init__(self, value = None):
		self.left = None
		self.op = None
		self.right = None

		self.value = value

def parse_expr():
	global tokens
	vnode = parse_term()

	while tokens and tokens[0] in ('+', '-'):
		op = tokens.pop(0)
		vnode_right = parse_term()
		new_vnode = node()
		new_vnode.op = op
		new_vnode.left = vnode
		new_vnode.right = vnode_right
		vnode = new_vnode
	
	return vnode

def parse_term():
	global tokens
	vnode = parse_factor()

	while tokens and tokens[0] in ('*', '/'):
		op = tokens.pop(0)
		vnode_right = parse_factor()
		new_vnode = node()
		new_vnode.op = op
		new_vnode.left = vnode
		new_vnode.right = vnode_right
		vnode = new_vnode
	
	return vnode

def parse_factor():
	global tokens
	token = tokens.pop(0)

	if token == '(':
		vnode = parse_expr()
		tokens.pop(0)  # remove ')'
		return vnode
	
	return node(token)

def evaluate(n):
    if n is None:
        return None

    if n.value is not None and n.value.isdigit():
        return int(n.value)

    left_value = evaluate(n.left)
    right_value = evaluate(n.right)

    if n.op == '+':
        return left_value + right_value
    elif n.op == '-':
        return left_value - right_value
    elif n.op == '*':
        return left_value * right_value
    elif n.op == '/':
        return left_value / right_value

while running:
	nodes = []
	expr = str(input(">> "))
	i = 0
	if expr.strip() == "exit":
		break
	
		# lexer
	while i < len(expr):
		if expr[i] in "1234567890":
			value = ""
			while i < len(expr) and expr[i] in "1234567890":
				value = value + expr[i]
				i = i + 1
			tokens.append(value)

		if i < len(expr) and expr[i] in "()+-*/":	
			tokens.append(expr[i])
	
		i = i + 1
	
		# parser, create nodes.
	
	if tokens != []:
		ast = parse_expr()
		print(evaluate(ast))

	tokens.clear()
