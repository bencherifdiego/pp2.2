#include "precomp.h"
#define MARGIN 0

void grid::Grid()
{
    // Clear the grid.
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            cells_[x][y] = NULL;
        }
    }
}

void grid::add(Tank* tank)
{
    //if (tank->active)
    {
        // Determine which grid cell it's in.
        int cellX = (int)(tank->position.x / grid::CELL_SIZE + MARGIN);
        int cellY = (int)(tank->position.y / grid::CELL_SIZE + MARGIN);

        /*cout << cellX;
        cout << "    ";
        cout << cellY << endl;*/

        // Add to the front of list for the cell it's in.
        tank->prev_ = nullptr;
        tank->next_ = cells_[cellX][cellY];
        cells_[cellX][cellY] = tank;

        if (tank->next_ != nullptr)
        {
            tank->next_->prev_ = tank;
        }
    }
}

void grid::processTanks()
{
    for (int y = 0; y < NUM_CELLS; y++)
    {
        for (int x = 0; x < NUM_CELLS; x++)
        {
            handleCell(/*cells_[x][y]*/ x, y);
        }
    }
}

void grid::handleCell(/*Tank* tank*/ int x, int y)
{
    //while (tank != nullptr)
    //{
    //    //cout << "test" << endl;
    //    Tank* other = tank->next_;
    //    while (other != nullptr)
    //    {
    //        if (tank->position.x == other->position.x && tank->position.y == other->position.y)
    //        {
    //            handleNudge(tank, other);
    //        }
    //        other = other->next_;
    //    }

    //    tank = tank->next_;
    //}

    //cout << "test" << endl;

    Tank* tank = cells_[x][y];
    while (tank != nullptr)
    {
        handleTank(tank, tank->next_);

        if (x > 0 && y > 0) handleTank(tank, cells_[x - 1][y - 1]);
        if (x > 0) handleTank(tank, cells_[x - 1][y]);
        if (y > 0) handleTank(tank, cells_[x][y - 1]);
        if (x > 0 && y < NUM_CELLS - 1) handleTank(tank, cells_[x - 1][y + 1]);
        if (y < NUM_CELLS - 1) handleTank(tank, cells_[x][y + 1]);
        if (y < NUM_CELLS - 1 && x < NUM_CELLS - 1) handleTank(tank, cells_[x + 1][y + 1]);
        if (x < NUM_CELLS - 1) handleTank(tank, cells_[x + 1][y]);
        if (x < NUM_CELLS - 1 && y > 0) handleTank(tank, cells_[x + 1][y - 1]);

        if (tank->next_ != nullptr)
        {
            tank = tank->next_;
        }
        else
        {
            break;
        }
    }
}

void grid::move(Tank* tank, double x, double y)
{
    // See which cell it was in.
    int oldCellX = (int)(tank->position.x / grid::CELL_SIZE + MARGIN);
    int oldCellY = (int)(tank->position.y / grid::CELL_SIZE + MARGIN);

    // See which cell it's moving to.
    int cellX = (int)(x / grid::CELL_SIZE + MARGIN);
    int cellY = (int)(y / grid::CELL_SIZE + MARGIN);

    tank->position.x = x;
    tank->position.y = y;

    // If it didn't change cells, we're done.
    if (oldCellX == cellX && oldCellY == cellY) return;

    // Unlink it from the list of its old cell.
    if (tank->prev_ != nullptr)
    {
        tank->prev_->next_ = tank->next_;
    }

    if (tank->next_ != nullptr)
    {
        tank->next_->prev_ = tank->prev_;
    }

    // If it's the head of a list, remove it.
    if (cells_[oldCellX][oldCellY] == tank)
    {
        cells_[oldCellX][oldCellY] = tank->next_;
    }

    // Add it back to the grid at its new cell.
    add(tank);
}

void grid::handleTank(Tank* tank, Tank* other)
{
    while (other != nullptr)
    {
        if (tank != other)
        {
            handleNudge(tank, other);
        }
        if (other->next_ != nullptr)
        {
            other = other->next_;
        }
        else
        {
            break;
        }
    }
}

void grid::handleNudge(Tank* tank, Tank* other)
{
    if (&tank != &other)
    {
        vec2 dir = tank->Get_Position() - other->Get_Position();
        float dirSquaredLen = dir.sqrLength();

        float colSquaredLen = (tank->Get_collision_radius() * tank->Get_collision_radius()) + (other->Get_collision_radius() * other->Get_collision_radius());

        if (dirSquaredLen < colSquaredLen)
        {
            tank->Push(dir.normalized(), 1.f);
        }
    }
}