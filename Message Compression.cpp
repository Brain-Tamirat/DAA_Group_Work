#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

struct TrafficQueues {
    int north = 0;
    int south = 0;
    int east = 0;
    int west = 0;
};

struct IntersectionState {
    bool phaseNS; // True for North-South, False for East-West
    int timer = 0;
};

const int ROWS = 2;
const int COLS = 2;
const int MIN_GREEN = 5;
const int MAX_GREEN = 30;
const int FLOW_RATE = 3;
const double THRESHOLD = 1.2;
const int TOTAL_STEPS = 1000;

class GridTrafficSystem {
private:
    TrafficQueues queues[ROWS][COLS];
    IntersectionState states[ROWS][COLS];
    int totalExited = 0;
    long totalWaitingTime = 0;
    int generationRate = 10; // 10% chance per time step

public:
    GridTrafficSystem() {
        // Initialize all intersections to North-South phase
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                states[i][j] = {true, 0};
            }
        }
    }
    void generateVehicles() {
        // Generate vehicles at top border (northbound)
        for (int j = 0; j < COLS; j++) {
            if (rand() % 100 < generationRate) {
                queues[0][j].north++;
            }
        }
        // Generate vehicles at left border (westbound)
        for (int i = 0; i < ROWS; i++) {
            if (rand() % 100 < generationRate) {
                queues[i][0].west++;
            }
        }
    }

    void processIntersection(int i, int j, int& exited) {
        // Update timer and check for phase switch
        states[i][j].timer++;
        if (states[i][j].timer >= MIN_GREEN) {
            int currentPhaseQueues, alternativePhaseQueues;

            if (states[i][j].phaseNS) {
                currentPhaseQueues = queues[i][j].north + queues[i][j].south;
                alternativePhaseQueues = queues[i][j].east + queues[i][j].west;
            } else {
                currentPhaseQueues = queues[i][j].east + queues[i][j].west;
                alternativePhaseQueues = queues[i][j].north + queues[i][j].south;
            }

            if (alternativePhaseQueues > THRESHOLD * currentPhaseQueues ||
                states[i][j].timer >= MAX_GREEN) {
                states[i][j].phaseNS = !states[i][j].phaseNS;
                states[i][j].timer = 0;
            }
        }

        // Process vehicles based on current phase
        if (states[i][j].phaseNS) {
            // Process North queue (vehicles going South)
            int moveNorth = std::min(FLOW_RATE, queues[i][j].north);
            queues[i][j].north -= moveNorth;

            if (i + 1 < ROWS) {
                queues[i + 1][j].north += moveNorth; // Move to next intersection's north queue
            } else {
                exited += moveNorth; // Exit the grid
            }

            // Process South queue (vehicles going North)
            int moveSouth = std::min(FLOW_RATE, queues[i][j].south);
            queues[i][j].south -= moveSouth;

            if (i - 1 >= 0) {
                queues[i - 1][j].south += moveSouth; // Move to previous intersection's south queue
            } else {
                exited += moveSouth; // Exit the grid
            }
        } else {
            // Process East queue (vehicles going East)
            int moveEast = std::min(FLOW_RATE, queues[i][j].east);
            queues[i][j].east -= moveEast;

            if (j + 1 < COLS) {
                queues[i][j + 1].east += moveEast; // Move to next intersection's east queue
            } else {
                exited += moveEast; // Exit the grid
            }

            // Process West queue (vehicles going West)
            int moveWest = std::min(FLOW_RATE, queues[i][j].west);
            queues[i][j].west -= moveWest;

            if (j - 1 >= 0) {
                queues[i][j - 1].west += moveWest; // Move to previous intersection's west queue
            } else {
                exited += moveWest; // Exit the grid
            }
        }
    }

void simulateStep() {
        generateVehicles();
        int exitedThisStep = 0;

        // Process each intersection
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                processIntersection(i, j, exitedThisStep);
            }
        }

        totalExited += exitedThisStep;

        // Calculate total vehicles in system
        int totalQueued = 0;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                totalQueued += queues[i][j].north + queues[i][j].south +
                               queues[i][j].east + queues[i][j].west;
            }
        }
        totalWaitingTime += totalQueued;
    }

    void printStatistics() const {
        std::cout << "\n====== Traffic Simulation Results ======\n";
        std::cout << "Grid size: " << ROWS << "x" << COLS << " intersections\n";
        std::cout << "Simulation duration: " << TOTAL_STEPS << " time steps\n";
        std::cout << "Total vehicles exited: " << totalExited << "\n";
        std::cout << "Average waiting time: "
                  << std::fixed << std::setprecision(2)
                  << (totalExited > 0 ? static_cast<double>(totalWaitingTime) / totalExited : 0)
                  << " timesteps per vehicle\n";
        std::cout << "Average queue length: "
                  << static_cast<double>(totalWaitingTime) / TOTAL_STEPS << "\n";

        std::cout << "\nFinal queue lengths:\n";
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                std::cout << "Intersection (" << i << "," << j << "): "
                          << "N=" << queues[i][j].north << " "
                          << "S=" << queues[i][j].south << " "
                          << "E=" << queues[i][j].east << " "
                          << "W=" << queues[i][j].west << "\n";
            }
        }
    }
};

int main() {
    return 0;
}
