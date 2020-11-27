pipeline {
  agent any
  stages {
    stage('Inicio') {
      steps {
        echo 'Iniciando...'
        sh 'env'
      }
    }

    stage('Instalacion') {
      steps {
        sh 'gcc -v'
      }
    }

    stage('saludo') {
      steps {
        sh '''gcc -o saludo programa.c
./saludo'''
      }
    }

  }
}