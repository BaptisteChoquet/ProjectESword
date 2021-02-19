package com.company;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Window extends JFrame {

    JProgressBar progress;

    public Window() {
        super("Armure");
        setSize(400, 600);

        JPanel monPanel = new JPanel();
        this.setContentPane(monPanel);


        GridBagLayout myLayout = new GridBagLayout();
        monPanel.setLayout(myLayout);

        ImageIcon img = new ImageIcon("casques.png");
        JButton tete = new JButton("Head", img);
        monPanel.add(tete);

        tete.setPreferredSize(new Dimension(50,60));

        JButton brasD = new JButton("Right Arm");
        monPanel.add(brasD);

        JButton buste = new JButton("Chest");
        monPanel.add(buste);
        buste.setPreferredSize(new Dimension(90,100));

        JButton brasG = new JButton("Left Arm");
        monPanel.add(brasG);

        JButton dos = new JButton("Back");
        monPanel.add(dos);
        dos.setPreferredSize(new Dimension(90,100));

        JButton jambes = new JButton("Legs");
        monPanel.add(jambes);
        jambes.setPreferredSize(new Dimension(50,100));

        JButton retour = new JButton("retour");
        monPanel.add(retour);

        // Créer le progressBar
        progress = new JProgressBar(0, 100);
        // Initialiser le progressBar à 0
        progress.setValue(100);
        // Afficher la chaîne de progression
        progress.setStringPainted(true);
        // Ajouter le progressBar au frame
        monPanel.add(progress);

        tete.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                int degat = 10;
                progress.setValue(progress.getValue() - degat);
            }
        });

        brasD.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                int degat = 2;
                progress.setValue(progress.getValue() - degat);
            }
        });

        brasG.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                int degat = 2;
                progress.setValue(progress.getValue() - degat);
            }
        });

        buste.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                int degat = 6;
                progress.setValue(progress.getValue() - degat);
            }
        });

        jambes.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                int degat = 2;
                progress.setValue(progress.getValue() - degat);
            }
        });

        dos.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                int degat = 5;
                progress.setValue(progress.getValue() - degat);
            }
        });

        retour.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                int reload = 100;
                progress.setValue(progress.getValue() + reload);
            }
        });


        GridBagConstraints gbc = new GridBagConstraints();

        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        monPanel.add(tete, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        monPanel.add(brasG, gbc);

        gbc.gridx = 1;
        gbc.gridy = 1;
        gbc.gridheight = 2;
        gbc.gridwidth = 1;
        monPanel.add(buste, gbc);

        gbc.gridx = 2;
        gbc.gridy = 1;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        monPanel.add(brasD, gbc);

        gbc.gridx = 3;
        gbc.gridy = 1;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        monPanel.add(dos, gbc);

        gbc.gridx = 1;
        gbc.gridy = 3;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        monPanel.add(jambes, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.gridheight = 1;
        gbc.gridwidth = 2;
        monPanel.add(progress, gbc);

        gbc.gridx = 3;
        gbc.gridy = 5;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        monPanel.add(retour, gbc);


    }
}
