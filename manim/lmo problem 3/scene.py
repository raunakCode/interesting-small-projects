from manim import *

class mathy(Scene):
    def construct(self):

        question1 = Tex("\\textbf{Problem 3.} For every positive integer \\textit{k}, a function \\textit{$f_k$} is defined as: \\textit{$f_{k}(x) = (-1)^k \\cdot kx + k - 17$}", font_size = 30)
        question2 = Tex("Determine the greatest positive integer n such that the following equation has a positive solution.", font_size = 30)
        question2.set_color_by_tex("n", BLUE)
        qdefinition = MathTex("\\textit{$ f_{1}(x)+f_{2}(x) + \\ldots + f_{2n}(x) = 0 $}", font_size = 30)
        question1.move_to(UP*3.5)
        question2.next_to(question1, DOWN, buff = 0.5)
        qdefinition.next_to(question2, DOWN, buff = 0.5)

        self.play(Write(question1))
        self.play(Write(question2))
        self.play(Write(qdefinition))
        self.wait(1.5)

        fdefinition = Tex("\\textit{$f_{k}(x) = (-1)^k \\cdot kx + k - 17$}", font_size = 45)
        transformed_qdefinition = MathTex("\\textit{$ S = f_{1}(x)+f_{2}(x) + \\ldots + f_{2n}(x) = 0 $}", font_size = 45)
        transformed_qdefinition.set_color_by_tex("S", RED)
        fdefinition.to_edge(UP)
        transformed_qdefinition.next_to(fdefinition, DOWN, buff = 0.5)

        self.remove(qdefinition)
        self.play(ReplacementTransform(question1, fdefinition), ReplacementTransform(question2, transformed_qdefinition), run_time = 1.5)
        self.wait(3)

        twoNfunctions = VGroup()
        f1 = MathTex("\\textit{$ f_{1}(x) = -x + 1 - 17 $}", font_size = 30)
        f2 = MathTex("\\textit{$ f_{2}(x) = 2x + 2 - 17 $}", font_size = 30)
        f3 = MathTex("\\textit{$ f_{3}(x) = -3x + 3 - 17 $}", font_size = 30)
        verticalDots = MathTex("\\vdots")
        f2n = MathTex("+ \\hspace{1mm} \\textit{$ f_{2n}(x) = 2nx + 2n - 17 $}", font_size = 30)

        answer1 = MathTex("\\textit{$ S = nx + \\frac{2n(2n+1)}{2} -17(2n) = 0 $}", font_size = 28)
        answer2 = MathTex("\\textit{$ S = nx + n(2n+1) -34n = 0 $}", font_size = 30)
        answer3 = MathTex("\\textit{$ S = nx + 2n^{2} -33n = 0 $}", font_size = 30)
        answer4 = MathTex("\\textit{$ S = n(x + 2n -33) = 0 $}", font_size = 30)

        answer1.set_color_by_tex("S", RED)
        answer2.set_color_by_tex("S", RED)
        answer3.set_color_by_tex("S", RED)
        answer4.set_color_by_tex("S", RED)

        final = MathTex("\\textbf{\\textit{$\\Longrightarrow n = 16 $}}", color = BLUE, font_size = 30)

        f1.next_to(fdefinition, DOWN, buff = 0)
        twoNfunctions.add(f1,f2,verticalDots,f2n,answer1,answer2,answer3,answer4,final)
        twoNfunctions.arrange(DOWN, buff = 0.3).shift(UP)

        self.play(FadeOut(fdefinition), ReplacementTransform(transformed_qdefinition, f1))
        for i in range(1, 4):
            self.play(Write(twoNfunctions[i]), run_time = 0.8)

        self.wait(3)

        for i in range(4,8):
            self.play(Write(twoNfunctions[i]), run_time = 0.8)

        self.wait(1.5)
        self.play(Write(twoNfunctions[8]), run_time = 1)

        self.wait(1.3)

        
        
        
