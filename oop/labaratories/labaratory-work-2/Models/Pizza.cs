namespace labaratory_work_2.Models
{
    public enum Dough
    {
        Thin,
        Thick
    }

    public class Pizza(string name, int weight, double price)
        : Dish(name, weight, price)
    {
        public Dough Dough { get; private set; } = Dough.Thick;

        public void ChangeDough()
        {
            Dough = Dough == Dough.Thin ? Dough.Thick : Dough.Thin;
        }

        public static void CutIntoSlices()
        {
            Console.WriteLine("Cutting the pizza into slices...");
        }

        public override void DisplayInfo()
        {
            Console.WriteLine($"Pizza: {Name}, {Dough} dough, {Weight}g, ${Price:F2}");
        }

        public override double GetFullPrice()
        {
            return Dough == Dough.Thin ? Price * 1.3 : Price * 1.5;
        }
    }
}
