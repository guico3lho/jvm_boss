class _conta {
    private static int contador = 0;
    
    private int numero;
    
    private double saldo;
    
    _conta(double paramDouble) {
      this.saldo = paramDouble;
      this.numero = contador++;
    }
    
    int obterNumero() {
      return this.numero;
    }
    
    double obterSaldo() {
      return this.saldo;
    }
    
    void debitar(double paramDouble) {
      this.saldo -= paramDouble;
    }
    
    void creditar(double paramDouble) {
      this.saldo += paramDouble;
    }
  }