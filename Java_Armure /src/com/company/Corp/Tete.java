package com.company.Corp;

public class Tete {
    private float shield = 1.5F;

    public Tete (int myDamageMul) {
        this.shield = myDamageMul;

    }

    public int getMyDamageMul() {

        return (int) this.shield;
    }
}
