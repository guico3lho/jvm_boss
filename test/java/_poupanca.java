class Poupanca extends _conta {
    Poupanca(double paramDouble) {
      super(paramDouble);
    }
    
    void atualizacaoMensal() {
      creditar(obterSaldo() * 0.005D);
    }
  }