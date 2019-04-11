/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <libsolidity/formal/EncodingContext.h>

#include <libsolidity/formal/SymbolicTypes.h>

using namespace std;
using namespace dev;
using namespace dev::solidity;
using namespace dev::solidity::smt;

EncodingContext::EncodingContext(SolverInterface& _solver):
	m_solver(_solver)
{
	reset();
}

void EncodingContext::reset()
{
	resetBalances();
}

void EncodingContext::resetBalances()
{
	auto sort = make_shared<smt::ArraySort>(
		make_shared<smt::Sort>(smt::Kind::Int),
		make_shared<smt::Sort>(smt::Kind::Int)
	);
	m_balances = make_shared<smt::Expression>(m_solver.newVariable("balances", sort));
}

smt::Expression EncodingContext::balance(smt::Expression _account)
{
	auto balance = smt::Expression::select(*m_balances, std::move(_account));
	auto intType = make_shared<IntegerType>(256);
	setSymbolicUnknownValue(balance, intType, m_solver);
	return balance;
}
