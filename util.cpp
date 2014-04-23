#include "util.h"

Position::Position(size_t _x, size_t _y) :
    x(_x),
    y(_y)
{}

Position::Position(const Position &_other) :
    x(_other.x),
    y(_other.y)
{}

Position Position::operator =(Position &_other)
{
    x = _other.x;
    y = _other.y;
    return *this;
}

void Position::print()
{
    cout << "x: " << x << ", y: " << y << endl;
}

Table::Table(bool _turn, size_t n) :
    m_turn(_turn),
    m_size(n)
{
    m_table.resize(n*n, unplayed);
}

Table::Table(Table &other) :
    m_turn(other.m_turn),
    m_size(other.m_size)
{
    m_table = other.m_table;
}

bool Table::marcar(Position _pt)
{
    size_t pos = m_size*_pt.y + _pt.x;
    if(m_table[pos] != unplayed)
        return false;
    m_table[pos] = (m_turn) ? played_op : played_me;
    m_turn = !m_turn;
    return true;
}

void Table::check(size_t &_w1, size_t &_w2)
{
    _w1 = _w2 = 0;
    //Verificar columnas completas
    for(size_t i = 0; i < m_size; ++i) {
        if(m_table[i] != unplayed) {
            for(size_t j = 0; j < m_size; ++j) {
                if(m_table[j*m_size + i] != m_table[i])
                    break;
                if(j == m_size-1) {
                    if(m_table[i] == played_me)
                        ++_w1;
                    else
                        ++_w2;
                }
            }
        }
    }
    //Verificar filas completas
    for(size_t j = 0; j < m_size; ++j) {
        if(m_table[j] != unplayed) {
            for(size_t i = 0; i < m_size; ++i) {
                if(m_table[j*m_size + i] != m_table[j])
                    break;
                if(i == m_size-1) {
                    if(m_table[j] == played_me)
                        ++_w1;
                    else
                        ++_w2;
                }
            }
        }
    }
    //Verificar diagonales
    if(m_table[0] != unplayed) {
        for(size_t i = 1; i < m_size; ++i){
            if(m_table[i*m_size+i] != m_table[0])
                break;
            if(i == m_size-1) {
                if(m_table[0] == played_me)
                    ++_w1;
                else
                    ++_w2;
            }
        }
    }
    else {
        if(m_table[m_size-1] != unplayed) {
            for(size_t i = 1; i < m_size; ++i) {
                if(m_table[i*m_size + m_size-i-1] != m_table[m_size-1])
                    break;
                if(i == m_size-1) {
                    if(m_table[m_size-1] == played_me)
                        ++_w1;
                    else
                        ++_w2;
                }
            }
        }
    }
}

void Table::availablePositions(vector<Position> &_pos)
{
    _pos.clear();
    Position tmp;
    for(size_t i = 0; i < m_size; ++i) {
        for(size_t j = 0; j < m_size; ++j) {
            if(m_table[i * m_size + j] == unplayed) {
                tmp.y = i;
                tmp.x = j;
                _pos.push_back(tmp);
            }
        }
    }
}

Game::Game(bool _start_me, size_t _n) :
    m_gameTable(_start_me,_n)
{}

void Game::play(Position _pos)
{
    if(_pos.x < m_gameTable.m_size && _pos.y < m_gameTable.m_size)
        m_gameTable.marcar(_pos);
    else
        return; //RETORNAR UNA EXCEPCIÓN PODRÍA SER MEJOR OPCIÓN

//****FUNCIONES ALTERNATIVAS, BORRARLAS CUANDO SE PUEDA****//
    draw();
    status winner = checkWinner();
    switch (winner) {
    case played_me:
        cout << "I won!" << endl;
        break;
    case played_op:
        cout << "You won!" << endl;
        break;
    default:
        break;
    }
    cout << endl;

//*********************************************************//
}

status Game::checkWinner()
{
    size_t  w1,
            w2;
    m_gameTable.check(w1, w2);
    if(w1)
        return played_me;
    if(w2)
        return played_op;
    return unplayed;
}

void Game::draw()
{
    for(size_t i = 0; i < m_gameTable.m_size; ++i) {
        for(size_t j = 0; j < m_gameTable.m_size; ++j) {
            status val = m_gameTable.m_table[i*m_gameTable.m_size + j];
            switch (val) {
            case unplayed:
                cout << "- ";
                break;
            case played_me:
                cout << "x ";
                break;
            case played_op:
                cout << "/ ";
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
}
