#pragma once
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Logger.h"

class GraphProcessor {
private:
    int numVertices = 0; // Изменили size_t на int, чтобы убрать ошибку
    std::vector<std::list<int>> adjList; 

    void DFS(int v, std::vector<bool>& visited, std::vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) DFS(neighbor, visited, component);
        }
    }

public:
    void loadFromFile(const std::string& filename) {
        LOG_INFO("Загрузка файла: " + filename);
        std::ifstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Файл не найден.");

        std::string line;
        if (!std::getline(file, line)) throw std::runtime_error("Файл пуст.");
        
        numVertices = std::stoi(line);
        // Защита: граф не может быть отрицательного размера
        if (numVertices < 0) throw std::runtime_error("Неверное количество вершин.");

        adjList.assign(numVertices + 1, std::list<int>());

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            int u, v;
            if (!(ss >> u)) continue;
            while (ss >> v) {
                if (u <= numVertices && v <= numVertices) adjList[u].push_back(v);
            }
        }
        LOG_INFO("Граф загружен. Вершин: " + std::to_string(numVertices));
    }

    void process(const std::string& outPath) {
        if (numVertices <= 0) throw std::runtime_error("Граф не загружен.");
        
        std::vector<bool> visited(numVertices + 1, false);
        std::vector<std::vector<int>> components;

        for (int i = 1; i <= numVertices; ++i) { // Изменили size_t на int
            if (!visited[i]) {
                std::vector<int> comp;
                DFS(i, visited, comp);
                components.push_back(comp);
            }
        }

        std::ofstream out(outPath);
        out << "Компонент: " << components.size() << "\n";
        for (int i = 0; i < (int)components.size(); ++i) { // Добавили явное приведение типов (int)
            out << i + 1 << ": ";
            for (int v : components[i]) out << v << " ";
            out << "\n";
        }
        LOG_INFO("Результат сохранен в " + outPath);
    }
};