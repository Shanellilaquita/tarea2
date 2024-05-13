#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

class AnalizadorDeDatos {
public:
    AnalizadorDeDatos(const std::string& rutaArchivo) : rutaArchivo_(rutaArchivo) {
        LeerDatos();
    }

    void CalcularEstadisticas() {
        if (datos_.empty()) {
            std::cerr << "El archivo está vacío." << std::endl;
            return;
        }

        auto moda = CalcularModa();
        auto media = CalcularMedia();

        MostrarResultados(moda, media);
    }

private:
    std::string rutaArchivo_;
    std::vector<double> datos_;

    void LeerDatos() {
        std::ifstream archivo(rutaArchivo_);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return;
        }

        std::copy(std::istream_iterator<double>(archivo),
                  std::istream_iterator<double>(),
                  std::back_inserter(datos_));
        archivo.close();
    }

    double CalcularModa() const {
        std::map<double, int> frecuencias;
        for (double valor : datos_) {
            frecuencias[valor]++;
        }

        double moda = 0.0;
        int maxFrecuencia = 0;
        for (const auto& par : frecuencias) {
            if (par.second > maxFrecuencia) {
                maxFrecuencia = par.second;
                moda = par.first;
            }
        }

        return moda;
    }

    double CalcularMedia() const {
        double suma = 0.0;
        for (double valor : datos_) {
            suma += valor;
        }
        return suma / datos_.size();
    }

    void MostrarResultados(double moda, double media) const {
        std::cout << "Información***** " << std::endl;
        std::cout << "Moda: " << moda << std::endl;
        std::cout << "Media: " << media << std::endl;
    }
};

int main() {
    AnalizadorDeDatos analizador("C:/Users/Admin/Desktop/datosLP.txt");
    analizador.CalcularEstadisticas();
    return 0;
}
